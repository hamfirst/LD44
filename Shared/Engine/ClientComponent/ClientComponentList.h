#pragma once

#include "Foundation/SkipField/SkipField.h"


template <typename ClientComponentType>
class ClientComponentList
{
public:

  NotNullPtr<ClientComponentType> AllocateComponent()
  {
    auto ptr = m_ComponentAllocator.Allocate();
    return ptr;
  }

  template <typename InitData>
  NotNullPtr<ClientComponentType> AllocateComponent(InitData && init_data)
  {
    auto ptr = m_ComponentAllocator.Allocate(std::forward<InitData>(init_data));
    return ptr;
  }

  void FreeComponent(NotNullPtr<ClientComponentType> component)
  {
    m_ComponentAllocator.Release(component);
  }

  NullOptPtr<ClientComponent> ResolveHandle(const ClientComponentHandle & handle)
  {
    return static_cast<NullOptPtr<ClientComponent>>(m_ComponentAllocator.ResolveHandle(handle));
  }

  template <typename Callable>
  void VisitAll(Callable && callable)
  {
    m_ComponentAllocator.VisitAll(std::forward<Callable>(callable));
  }

private:
  SkipField<ClientComponentType> m_ComponentAllocator;
};
