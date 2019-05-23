#pragma once

#include "Runtime/ServerEntity/ServerObjectOverlapSystem.h"
#include "StormRefl/StormReflMetaCall.h"

template <typename DataType, bool IsOverlap>
struct RegisterServerEntityOverlap
{
  template <typename ParamType>
  static void Process()
  {

  }
};

template <typename DataType>
struct RegisterServerEntityOverlap<DataType, true>
{
  template <typename ParamType>
  static void Process()
  {
    g_ServerEntityOverlapSystem.RegisterEntityInteraction(DataType::TypeIndex, ParamType::TypeIndex);
  }
};



template <typename DataType>
void RegisterServerEntityOverlapCallbacks()
{
  auto visitor = [&](auto f)
  {
    constexpr uint32_t FuncNameHash = f.GetFunctionNameHash();
    constexpr bool IsOverlap = (FuncNameHash == 0xB0B10809); // "OnOverlap"
    using FuncType = decltype(f);
    using ParamType = typename std::decay_t<typename FuncType::template param_info<0>::param_type>;

    RegisterServerEntityOverlap<DataType, IsOverlap>::template Process<ParamType>();
  };

  StormReflFuncVisitor<DataType>::VisitFuncs(visitor);
}


#define REGISTER_SERVER_ENTITY_OVERLAP(DataClass, Sprite) \
  struct s_##DataClass##OverlapInit \
  { \
    s_##DataClass##OverlapInit() \
    { \
      g_ServerEntityOverlapSystemRegister.AddCall([] { \
        g_ServerEntityOverlapSystem.RegisterEntityType(DataClass::TypeIndex, &Sprite, COMPILE_TIME_CRC32_STR("MoveBox")); \
      }); \
      g_ServerEntityOverlapSystemInteractionRegister.AddCall([] { \
        RegisterServerEntityOverapCallbacks<DataClass>(); \
      }); \
    } \
  } s_##DataClass##OverlapInit_inst; \


