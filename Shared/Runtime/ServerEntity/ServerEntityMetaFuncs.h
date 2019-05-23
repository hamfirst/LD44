#pragma once

#include "StormRefl/StormReflMetaFuncs.h"
#include "Runtime/ServerEntity/ServerEntityHandle.h"

template <typename T>
struct ServerEntityResetHandle;

template <typename T, bool IsReflectable>
struct ServerEntityResetHandleClass
{
  static void Process(T & t, const ServerEntityManager & entity_manager)
  {

  }
};

template <typename T>
struct ServerEntityResetHandleClass<T, true>
{
  static void Process(T & t, const ServerEntityManager & entity_manager)
  {
    auto visitor = [&](auto f)
    {
      using MemberType = typename decltype(f)::member_type;
      ServerEntityResetHandle<MemberType>::Process(f.Get(), entity_manager);
    };

    StormReflVisitEach(t, visitor);
  }
};

template <typename T>
struct ServerEntityResetHandle
{
  static void Process(T & t, const ServerEntityManager & entity_manager)
  {
    ServerEntityResetHandleClass<T, StormReflCheckReflectable<T>::value>::Process(t, entity_manager);
  }
};

template <>
struct ServerEntityResetHandle<ServerEntityHandle>
{
  static void Process(ServerEntityHandle & handle, const ServerEntityManager & entity_manager)
  {
    handle.ResetGen(entity_manager);
  }
};

