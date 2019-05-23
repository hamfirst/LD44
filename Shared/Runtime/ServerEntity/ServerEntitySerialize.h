#pragma once

#include "StormNet/NetSerialize.h"
#include "StormNet/NetDeserialize.h"

#include "Runtime/ServerEntity/ServerEntityManager.h"

class ServerEntityManager;

class ServerEntityNetBitWriter
{
public:
  ServerEntityNetBitWriter(NetBitWriter & writer, NotNullPtr<const ServerEntityManager> server_entity_manager);

  void WriteBits(uint64_t val, int num_bits);
  void WriteSBits(int64_t val, int num_bits);

  void WriteBits(NetBitWriterCursor & cursor, uint64_t val, int num_bits);
  void WriteSBits(NetBitWriterCursor & cursor, int64_t val, int num_bits);

  void WriteBuffer(void * data, std::size_t num_bytes);

  NetBitWriterCursor Reserve(int num_bits);
  void RollBack(NetBitWriterCursor & cursor);

  NotNullPtr<const ServerEntityManager> GetServerManager();

  operator NetBitWriter & ();
  operator const NetBitWriter & () const;

  template <typename T>
  const T * GetParentObjectAs()
  {
    m_Writer.GetParentObjectAs<T>();
  }

  template <typename T>
  void SetParentObject(const T * t)
  {
    m_Writer.SetParentObject<T>(t);
  }

  void SetParentObject(const void * ptr, const void * (*cast)(std::size_t, const void *))
  {
    m_Writer.SetParentObject(ptr, cast);
  }

  auto GetParentObjectRaw() const { return m_Writer.GetParentObjectRaw(); }
  auto GetParentObjectCast() const { return m_Writer.GetParentObjectCast(); }

private:
  NetBitWriter & m_Writer;
  NotNullPtr<const ServerEntityManager> m_ServerEntityManager;
};

class ServerEntityNetBitReader
{
public:
  ServerEntityNetBitReader(NetBitReader & reader, NotNullPtr<ServerEntityManager> server_entity_manager);

  uint64_t ReadUBits(int num_bits);
  int64_t ReadSBits(int num_bits);

  void ReadBuffer(void * buffer, std::size_t num_bytes);

  NotNullPtr<ServerEntityManager> GetServerManager();

  operator NetBitReader & ();
  operator const NetBitReader & () const;

  template <typename T>
  const T * GetParentObjectAs()
  {
    m_Reader.GetParentObjectAs<T>();
  }

  template <typename T>
  void SetParentObject(const T * t)
  {
    m_Reader.SetParentObject<T>(t);
  }

  void SetParentObject(const void * ptr, const void * (*cast)(std::size_t, const void *))
  {
    m_Reader.SetParentObject(ptr, cast);
  }

  auto GetParentObjectRaw() const { return m_Reader.GetParentObjectRaw(); }
  auto GetParentObjectCast() const { return m_Reader.GetParentObjectCast(); }

private:
  NetBitReader & m_Reader;
  NotNullPtr<ServerEntityManager> m_ServerEntityManager;
};


template <typename T, typename NetBitWriter>
void SerializeServerEntity(const T &t, NetBitWriter &writer)
{
  NetSerializer<T, NetBitWriter> serializer;
  serializer(t, writer);
}

template <typename T, typename NetBitReader>
void DeserializeServerEntity(T &t, NetBitReader &reader)
{
  NetDeserializer<T, NetBitReader> deserializer;
  deserializer(t, reader);
}

template <class NetBitWriter>
struct NetSerializer<ServerEntityManager, NetBitWriter>
{
  void operator()(const ServerEntityManager & val, NetBitWriter & writer)
  {
    val.Serialize(writer);
  }
};

template <class NetBitReader>
struct NetDeserializer<ServerEntityManager, NetBitReader>
{
  void operator()(ServerEntityManager & val, NetBitReader & reader)
  {
    val.Deserialize(reader);
  }
};

