
#include "Engine/EngineCommon.h"
#include "Engine/ClientComponent/ClientComponentHandle.h"

ClientComponentHandle::ClientComponentHandle() :
  m_ComponentStore(nullptr)
{

}

NullOptPtr<ClientComponent> ClientComponentHandle::Resolve()
{
  return m_ComponentStore ? ResolveFunc(*this, m_ComponentStore) : nullptr;
}

