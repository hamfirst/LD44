
#include "StormNet/NetBitWriterVector.h"

#include "StormNetSys/NetClientSystemHandler.h"
#include "StormNetSys/NetServerSystemManagerFullAuthorityServer.h"
#include "StormNetSys/NetServerSystemManagerFullAuthorityClient.h"

#include "UnitTests/StormNetSysTest/ClientSystemTest.h"
#include "UnitTests/StormNetSysTest/ServerSystemTest.refl.meta.h"

#include <gtest/gtest.h>

struct ServerAuthorityTest : public testing::Test
{
  ServerAuthorityTest() :
    server(ServerSystemTestInitInfo{}),
    client(ServerSystemTestInitInfo{})
  {

  }

  void Connect()
  {
    server.AddClient(0);
  }

  void Disconnect()
  {
    server.RemoveClient(0);
  }

  void SyncToClient()
  {
    NetBitWriterVector writer;
    server.SyncToClient(0, writer);

    NetBitReaderBuffer reader(writer.GetData(), writer.GetDataSize());
    client.SyncFromServer(reader);

    EXPECT_EQ(true, reader.IsEmpty());
  }

  void SyncToServer()
  {
    NetBitWriterVector writer;
    client.SyncToServer(writer);

    NetBitReaderBuffer reader(writer.GetData(), writer.GetDataSize());
    server.SyncFromClient(0, reader);

    EXPECT_EQ(true, reader.IsEmpty());
  }

  void AckToClient()
  {
    NetBitWriterVector writer;
    server.WriteAck(0, writer);

    NetBitReaderBuffer reader(writer.GetData(), writer.GetDataSize());
    client.AckFromServer(reader);

    EXPECT_EQ(true, reader.IsEmpty());
  }

  void AckToServer()
  {
    NetBitWriterVector writer;
    client.WriteAck(writer);

    NetBitReaderBuffer reader(writer.GetData(), writer.GetDataSize());
    server.AckFromClient(0, reader);

    EXPECT_EQ(true, reader.IsEmpty());
  }

  NetServerSystemManagerFullAuthorityServer<128, ServerSystemTest> server;
  NetServerSystemManagerFullAuthorityClient<ServerSystemTest> client;
};


struct ServerAuthorityTestAutoConnectAutoAck : public ServerAuthorityTest
{
  ServerAuthorityTestAutoConnectAutoAck()
  {
    Connect();
  }

  void SyncToServer()
  {
    ServerAuthorityTest::SyncToServer();
    ServerAuthorityTest::AckToClient();
  }

  void SyncToClient()
  {
    ServerAuthorityTest::SyncToClient();
    ServerAuthorityTest::AckToServer();
  }
};

// Test updating server/client
TEST_F(ServerAuthorityTest, TestUpdate)
{
  server.Update();
  client.Update();

  EXPECT_EQ(1, server.GetState<ServerSystemTest>().m_Frame);
  EXPECT_EQ(1, client.GetState<ServerSystemTest>().m_Frame);
}

// Test syncing from server to client
TEST_F(ServerAuthorityTestAutoConnectAutoAck, TestSync)
{
  server.Update();

  EXPECT_EQ(1, server.GetState<ServerSystemTest>().m_Frame);
  EXPECT_EQ(0, client.GetState<ServerSystemTest>().m_Frame);

  SyncToClient();

  EXPECT_EQ(1, server.GetState<ServerSystemTest>().m_Frame);
  EXPECT_EQ(1, client.GetState<ServerSystemTest>().m_Frame);

  server.Update();

  EXPECT_EQ(2, server.GetState<ServerSystemTest>().m_Frame);
  EXPECT_EQ(1, client.GetState<ServerSystemTest>().m_Frame);

  client.Update();

  EXPECT_EQ(2, server.GetState<ServerSystemTest>().m_Frame);
  EXPECT_EQ(2, client.GetState<ServerSystemTest>().m_Frame);

  SyncToClient();

  EXPECT_EQ(2, server.GetState<ServerSystemTest>().m_Frame);
  EXPECT_EQ(2, client.GetState<ServerSystemTest>().m_Frame);
}

TEST_F(ServerAuthorityTestAutoConnectAutoAck, TestInput)
{
  SyncToClient();
  server.Update();
  client.Update();

  ServerSystemTestInput inp;

  EXPECT_EQ(0, server.GetState<ServerSystemTest>().m_Inputs);
  EXPECT_EQ(0, client.GetState<ServerSystemTest>().m_Inputs);

  client.PushInput<ServerSystemTest>(inp);

  EXPECT_EQ(0, server.GetState<ServerSystemTest>().m_Inputs);
  EXPECT_EQ(0, client.GetState<ServerSystemTest>().m_Inputs);

  SyncToServer();

  EXPECT_EQ(1, server.GetState<ServerSystemTest>().m_Inputs);
  EXPECT_EQ(0, client.GetState<ServerSystemTest>().m_Inputs);

  server.Update();
  client.Update();

  EXPECT_EQ(1, server.GetState<ServerSystemTest>().m_Inputs);
  EXPECT_EQ(0, client.GetState<ServerSystemTest>().m_Inputs);

  SyncToClient();

  EXPECT_EQ(1, server.GetState<ServerSystemTest>().m_Inputs);
  EXPECT_EQ(1, client.GetState<ServerSystemTest>().m_Inputs);
}

// Test effect event reconciliation from server to client
TEST_F(ServerAuthorityTestAutoConnectAutoAck, TestReconciler)
{
  ServerSystemTestEffectEvent ev1;
  ev1.m_PositionX = 10;
  ev1.m_PositionY = 10;

  client.PushEffectEvent<ServerSystemTest>(ev1);
  EXPECT_EQ(1, client.GetClientSystemHandler<ServerSystemTest>().m_EffectEvents);

  server.PushEffectEvent<ServerSystemTest>(ev1);
  EXPECT_EQ(1, client.GetClientSystemHandler<ServerSystemTest>().m_EffectEvents);

  client.Update();
  server.Update();
  SyncToClient();
  EXPECT_EQ(1, client.GetClientSystemHandler<ServerSystemTest>().m_EffectEvents);
}

// Test authority events from server to client
TEST_F(ServerAuthorityTestAutoConnectAutoAck, TestAuthorityEvent)
{
  ServerSystemTestAuthorityEvent ev1;

  client.PushAuthorityEvent<ServerSystemTest>(ev1);
  EXPECT_EQ(0, client.GetClientSystemHandler<ServerSystemTest>().m_AuthorityEvents);

  server.PushAuthorityEvent<ServerSystemTest>(ev1);
  EXPECT_EQ(0, client.GetClientSystemHandler<ServerSystemTest>().m_AuthorityEvents);

  client.Update();
  server.Update();
  SyncToClient();
  EXPECT_EQ(1, client.GetClientSystemHandler<ServerSystemTest>().m_AuthorityEvents);
}

// Test client local data change
TEST_F(ServerAuthorityTestAutoConnectAutoAck, TestClientLocalData)
{
  EXPECT_EQ(0, client.GetClientSystemHandler<ServerSystemTest>().m_ClientLocalDataChanges);
  EXPECT_EQ(0, client.GetClientLocalData<ServerSystemTest>().m_Data);

  client.Update();
  server.Update();
  SyncToClient();
  EXPECT_EQ(1, client.GetClientSystemHandler<ServerSystemTest>().m_ClientLocalDataChanges);
  EXPECT_EQ(0, client.GetClientLocalData<ServerSystemTest>().m_Data);

  server.GetClientLocalDataForModify<ServerSystemTest>(0).m_Data = 1;
  EXPECT_EQ(1, server.GetClientLocalData<ServerSystemTest>(0).m_Data);

  client.Update();
  server.Update();
  SyncToClient();
  EXPECT_EQ(2, client.GetClientSystemHandler<ServerSystemTest>().m_ClientLocalDataChanges);
  EXPECT_EQ(1, client.GetClientLocalData<ServerSystemTest>().m_Data);
}

// Test client local events
TEST_F(ServerAuthorityTestAutoConnectAutoAck, TestClientLocalEvent)
{
  ServerSystemTestClientLocalEvent ev1;

  client.PushClientLocalEvent<ServerSystemTest>(ev1, 0);
  EXPECT_EQ(0, client.GetClientSystemHandler<ServerSystemTest>().m_ClientLocalEvents);

  server.PushClientLocalEvent<ServerSystemTest>(ev1, 0);
  EXPECT_EQ(0, client.GetClientSystemHandler<ServerSystemTest>().m_ClientLocalEvents);

  client.Update();
  server.Update();
  SyncToClient();
  EXPECT_EQ(1, client.GetClientSystemHandler<ServerSystemTest>().m_ClientLocalEvents);
}

int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
