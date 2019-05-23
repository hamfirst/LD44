
#include "Runtime/RuntimeCommon.h"
#include "Runtime/ServerEntity/ServerEntitySerialize.h"

ServerEntityNetBitWriter::ServerEntityNetBitWriter(NetBitWriter & writer, NotNullPtr<const ServerEntityManager> server_entity_manager) :
  m_Writer(writer),
  m_ServerEntityManager(server_entity_manager)
{

}

void ServerEntityNetBitWriter::WriteBits(uint64_t val, int num_bits)
{
  m_Writer.WriteBits(val, num_bits);
}

void ServerEntityNetBitWriter::WriteSBits(int64_t val, int num_bits)
{
  m_Writer.WriteSBits(val, num_bits);
}

void ServerEntityNetBitWriter::WriteBits(NetBitWriterCursor & cursor, uint64_t val, int num_bits)
{
  m_Writer.WriteBits(cursor, val, num_bits);
}

void ServerEntityNetBitWriter::WriteSBits(NetBitWriterCursor & cursor, int64_t val, int num_bits)
{
  m_Writer.WriteSBits(cursor, val, num_bits);
}

void ServerEntityNetBitWriter::WriteBuffer(void * data, std::size_t num_bytes)
{
  m_Writer.WriteBuffer(data, num_bytes);
}

NetBitWriterCursor ServerEntityNetBitWriter::Reserve(int num_bits)
{
  return m_Writer.Reserve(num_bits);
}

void ServerEntityNetBitWriter::RollBack(NetBitWriterCursor & cursor)
{
  m_Writer.RollBack(cursor);
}

NotNullPtr<const ServerEntityManager> ServerEntityNetBitWriter::GetServerManager()
{
  return m_ServerEntityManager;
}

ServerEntityNetBitWriter::operator NetBitWriter & ()
{
  return m_Writer;
}

ServerEntityNetBitWriter::operator const NetBitWriter & () const
{
  return m_Writer;
}

ServerEntityNetBitReader::ServerEntityNetBitReader(NetBitReader & reader, NotNullPtr<ServerEntityManager> server_entity_manager) :
  m_Reader(reader),
  m_ServerEntityManager(server_entity_manager)
{

}

uint64_t ServerEntityNetBitReader::ReadUBits(int num_bits)
{
  return m_Reader.ReadUBits(num_bits);
}

int64_t ServerEntityNetBitReader::ReadSBits(int num_bits)
{
  return m_Reader.ReadSBits(num_bits);
}

void ServerEntityNetBitReader::ReadBuffer(void * buffer, std::size_t num_bytes)
{
  m_Reader.ReadBuffer(buffer, num_bytes);
}

NotNullPtr<ServerEntityManager> ServerEntityNetBitReader::GetServerManager()
{
  return m_ServerEntityManager;
}

ServerEntityNetBitReader::operator NetBitReader & ()
{
  return m_Reader;
}

ServerEntityNetBitReader::operator const NetBitReader & () const
{
  return m_Reader;
}
