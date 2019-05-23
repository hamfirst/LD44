#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "IsAlertedBotConditional.refl.h"
#include "Game/GameFullState.refl.meta.h"
#include "Game/ServerEntities/Bot/BotServerObject.refl.meta.h"


template <>
struct StormReflTypeInfo<IsAlertedBotConditional>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "IsAlertedBotConditional"; }
  static constexpr auto GetNameHash() { return 0xAEA4C715; }
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<IsAlertedBotConditional *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const IsAlertedBotConditional *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<IsAlertedBotConditional *>(ptr);
    if(typeid(IsAlertedBotConditional).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const IsAlertedBotConditional *>(ptr);
    if(typeid(IsAlertedBotConditional).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

namespace StormReflFileInfo
{
  struct IsAlertedBotConditional
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct IsAlertedBotConditional::type_info<0>
  {
    using type = ::IsAlertedBotConditional;
  };

}

