#pragma once

#include "Engine/EngineCommon.h"

#include "Foundation/Handle/Handle.h"

class ClientComponent;
class ComponentManager;

template <typename T>
NullOptPtr<T> ComponentCast(NotNullPtr<ClientComponent> comp);

class ENGINE_EXPORT ClientComponentHandle : public SpecificHandle<ComponentManager>
{
public:
  ClientComponentHandle();
  ClientComponentHandle(const ClientComponentHandle & rhs) = default;
  ClientComponentHandle(ClientComponentHandle && rhs) = default;

  ClientComponentHandle & operator = (const ClientComponentHandle & rhs) = default;
  ClientComponentHandle & operator = (ClientComponentHandle && rhs) = default;

  NullOptPtr<ClientComponent> Resolve();

  template <typename T>
  NullOptPtr<T> ResolveTo()
  {
    auto comp = Resolve();
    if (comp)
    {
      return ComponentCast<T>(comp);
    }

    return nullptr;
  }

private:

  friend class ClientComponent;

  NullOptPtr<ClientComponent> (*ResolveFunc)(const ClientComponentHandle & handle, void * comp_store);
  void * m_ComponentStore;
};
