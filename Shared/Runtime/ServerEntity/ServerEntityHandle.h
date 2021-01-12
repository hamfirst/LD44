#pragma once

#include "Runtime/RuntimeCommon.h"

#include "StormNet/NetSerialize.h"
#include "StormNet/NetDeserialize.h"

class ServerEntity;
class ServerEntityManager;

class ServerEntityHandle
{
public:

  ServerEntityHandle();

  template <typename T>
  NullOptPtr<T> ResolveTo(const ServerEntityManager & entity_manager) const;

  NullOptPtr<ServerEntity> Resolve(const ServerEntityManager & entity_manager) const;

  void Reset();

  int GetRawSlotIndex() const;

  static ServerEntityHandle ConstructFromStaticIndex(int static_index);

private:

  void ResetGen(const ServerEntityManager & entity_manager);

  friend class ServerEntityManager;
  friend class ServerEntity;

  template <typename T>
  friend struct ServerEntityResetHandle;

  template <typename Type, class NetBitReader>
  friend struct NetSerializer;

  template <typename Type, class NetBitReader>
  friend struct NetDeserializer;

  int m_SlotId;
  int m_Gen;
};


template <class NetBitWriter>
struct NetSerializer<ServerEntityHandle, NetBitWriter>
{
  void operator()(const ServerEntityHandle & val, NetBitWriter & writer)
  {
    if (val.Resolve(writer.GetServerManager()) != nullptr)
    {
      writer.WriteBits(1, 1);
      writer.WriteBits(val.m_SlotId, writer.GetServerManager()->GetHandleBits());
    }
    else
    {
      writer.WriteBits(0, 1);
    }
  }
};

template <class NetBitReader>
struct NetDeserializer<ServerEntityHandle, NetBitReader>
{
  void operator()(ServerEntityHandle & h, NetBitReader & reader)
  {
    auto val = reader.ReadUBits(1);
    if (val)
    {
      auto server_manager = reader.GetServerManager();

      h.m_SlotId = (int)reader.ReadUBits(server_manager->GetHandleBits());
      h.m_Gen = server_manager->GetDynamicEntityGeneration(h.m_SlotId);
    }
    else
    {
      h.m_SlotId = -1;
      h.m_Gen = 0;
    }
  }
};



