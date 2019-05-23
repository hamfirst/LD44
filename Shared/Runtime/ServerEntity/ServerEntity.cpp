
#include "Runtime/RuntimeCommon.h"
#include "Runtime/ServerEntity/ServerEntity.h"
#include "Runtime/ServerEntity/ServerEntityManager.h"
#include "Runtime/ServerEntity/ServerEntitySerialize.h"
#include "Runtime/ServerEntity/ServerEntityEventRegister.h"
#include "Runtime/ServerEntity/ServerEntityRegistrationMacros.h"
#include "Runtime/ServerEntity/ServerEntityMetaFuncs.h"
#include "Runtime/ServerEntity/ServerEntitySystem.h"
#include "Runtime/ServerEntity/ServerObjectUpdate.h"
#include "Runtime/ServerEntity/ServerEntityEventDispatch.h"
#include "Runtime/ServerEntity/ServerEntityComponent.h"
#include "Runtime/ServerEntity/ServerEntityComponentFuncs.h"

#include "Foundation/SkipField/SkipField.h"
#include "Foundation/Update/UpdateRegistrationTemplates.h"

REGISTER_BASE_SERVER_ENTITY(ServerEntity);

ServerEntityHandle ServerEntity::GetEntityHandle() const
{
  return m_ServerEntityHandle;
}

const Handle & ServerEntity::GetHandle() const
{
  return m_Handle;
}

void ServerEntity::SetHandle(Handle & handle)
{
  m_Handle = handle;
}

void ServerEntity::SetIterator(const SkipFieldIterator & itr)
{
  m_Iterator = itr;
}

const SkipFieldIterator & ServerEntity::GetIterator() const
{
  return m_Iterator;
}

void ServerEntity::Destroy(ServerEntityManager & obj_manager)
{
  obj_manager.DestroyDynamicEntityInternal(this);
}

void ServerEntity::InitPosition(const Vector2 & pos)
{

}

czstr ServerEntity::GetDefaultEntityBinding() const
{
  return nullptr;
}

czstr ServerEntity::GetEntityBinding() const
{
  return GetDefaultEntityBinding();
}

Optional<int> ServerEntity::GetAssociatedPlayer(GameLogicContainer & game_container) const
{
  return {};
}

void ServerEntity::InitStaticComponents()
{

}

bool ServerEntity::IsDestroyed() const
{
  return m_IsDestroyed;
}

int ServerEntity::GetSlotIndex() const
{
  return m_SlotIndex;
}

int ServerEntity::GetLifetime() const
{
  return std::min(m_FramesAlive, 7);
}

int ServerEntity::GetTypeIndex() const
{
  return m_TypeIndex;
}

bool ServerEntity::TriggerEventHandler(uint32_t event_type, const void * ev, const EventMetaData & meta)
{
  if (m_EventDispatch == nullptr)
  {
    return true;
  }

  return m_EventDispatch->TriggerEventHandler(this, event_type, ev, meta);
}

const ServerEntityTypeInfo & ServerEntity::GetTypeInfo() const
{
  return g_ServerEntitySystem.GetTypeInfo(m_TypeIndex);
}

void ServerEntity::SetEventDispatch(NotNullPtr<ServerEntityEventDispatch> event_dispatch)
{
  m_EventDispatch = event_dispatch;
}
