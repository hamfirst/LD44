
#include "Runtime/RuntimeCommon.h"
#include "Runtime/ServerEntity/ServerEntityHandle.h"
#include "Runtime/ServerEntity/ServerEntityManager.h"

ServerEntityHandle::ServerEntityHandle() :
  m_SlotId(-1),
  m_Gen(0)
{
  
}

void ServerEntityHandle::Reset()
{
  m_SlotId = -1;
  m_Gen = 0;
}

void ServerEntityHandle::ResetGen(const ServerEntityManager & object_manager)
{
  if (Resolve(object_manager) == nullptr)
  {
    m_SlotId = -1;
    m_Gen = 0;
  }
  else
  {
    m_Gen = 0;
  }
}

int ServerEntityHandle::GetRawSlotIndex() const
{
  return m_SlotId;
}

ServerEntityHandle ServerEntityHandle::ConstructFromStaticIndex(int static_index)
{
  ServerEntityHandle handle;
  handle.m_SlotId = static_index;
  handle.m_Gen = 0;
  return handle;
}

NullOptPtr<ServerEntity> ServerEntityHandle::Resolve(const ServerEntityManager & object_manager) const
{
  return object_manager.ResolveHandle(m_SlotId, m_Gen);
}

template <>
NullOptPtr<ServerEntity> ServerEntityHandle::ResolveTo<ServerEntity>(const ServerEntityManager & object_manager) const
{
  return Resolve(object_manager);
}
