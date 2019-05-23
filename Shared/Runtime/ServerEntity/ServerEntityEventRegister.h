#pragma once

#include "StormRefl/StormReflMetaCall.h"
#include "Runtime/ServerEntity/ServerEntity.h"

template <typename ServerEntityType>
void RegisterServerEntityEvents()
{
  auto & event_dispatch = ServerEntityType::EventDispatch;
  StormReflFuncVisitor<ServerEntityType>::VisitFuncs([&](auto f)
  {
    auto func_ptr = f.GetFunctionPtr();
    event_dispatch.RegisterEventHandler(func_ptr);
  });
}




