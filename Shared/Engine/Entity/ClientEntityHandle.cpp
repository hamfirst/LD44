
#include "Engine/EngineCommon.h"

#include "Engine/Entity/ClientEntity.h"
#include "Engine/Entity/ClientEntityHandle.h"
#include "Engine/Entity/ClientEntitySystem.h"

NullOptPtr<ClientEntity> ClientEntityHandle::Resolve()
{
  return m_EntityManager ? m_EntityManager->ResolveHandle(*this) : nullptr;
}

void ClientEntityHandle::Destroy()
{
  auto entity = Resolve();
  if (entity)
  {
    entity->Destroy();
    m_EntityManager = nullptr;
  }
}
