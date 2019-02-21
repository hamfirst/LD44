#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "SpriteAnimationEventDef.refl.h"


template <>
struct StormReflTypeInfo<SpriteAnimationEventDataBase>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SpriteAnimationEventDataBase"; }
  static constexpr auto GetNameHash() { return 0x0131E8FB; }
  static constexpr bool HasDefault() { return true; }
  static SpriteAnimationEventDataBase & GetDefault() { static SpriteAnimationEventDataBase def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SpriteAnimationEventDataBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SpriteAnimationEventDataBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SpriteAnimationEventDataBase *>(ptr);
    if(typeid(SpriteAnimationEventDataBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SpriteAnimationEventDataBase *>(ptr);
    if(typeid(SpriteAnimationEventDataBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

namespace StormReflFileInfo
{
  struct SpriteAnimationEventDef
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct SpriteAnimationEventDef::type_info<0>
  {
    using type = ::SpriteAnimationEventDataBase;
  };

}

