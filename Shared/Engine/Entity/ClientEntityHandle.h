#pragma once

#include "Foundation/Handle/Handle.h"

#include "Engine/EngineCommon.h"

class ClientEntity;
class ClientEntitySystem;

class ENGINE_EXPORT ClientEntityHandle : public SpecificHandle<ClientEntitySystem>
{
public:
  NullOptPtr<ClientEntity> Resolve();

  void Destroy();
private:

  friend class ClientEntity;
  friend class ClientEntitySystem;

  NotNullPtr<ClientEntitySystem> m_EntityManager = nullptr;
};
