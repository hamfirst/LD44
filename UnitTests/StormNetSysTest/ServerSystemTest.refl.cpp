
#include "ServerSystemTest.refl.meta.h"

#include "StormNetSys/NetServerSystemHandlerSerialize.h"
#include "ServerSystemTest.refl.h"


ServerSystemTest::ServerSystemTest(const ServerSystemTestInitInfo & info)
{

}

void ServerSystemTest::Update()
{
  auto & state = GetStateForModify();
  state.m_Frame++;
}

void ServerSystemTest::ProcessInput(std::size_t client_index, const ServerSystemTestInput & input)
{
  auto & state = GetStateForModify();
  state.m_Inputs++;
}

void ServerSystemTest::ProcessExternalEvent(const ServerSystemTestExternalEvent & event)
{
  auto & state = GetStateForModify();
  state.m_ExternalEvents++;
}
