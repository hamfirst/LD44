#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "NPCSpawn.refl.h"
#include "Runtime/Anchor/AnchorDef.refl.meta.h"


template <>
struct StormReflTypeInfo<NPCSpawn>
{
  using MyBase = AnchorDataBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "NPCSpawn"; }
  static constexpr auto GetNameHash() { return 0x64C1893D; }
  static constexpr bool HasDefault() { return true; }
  static NPCSpawn & GetDefault() { static NPCSpawn def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<NPCSpawn *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x474FD0AA == type_name_hash) return static_cast<AnchorDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const NPCSpawn *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x474FD0AA == type_name_hash) return static_cast<const AnchorDataBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<NPCSpawn *>(ptr);
    if(typeid(NPCSpawn).hash_code() == type_id_hash) return c;
    if(typeid(AnchorDataBase).hash_code() == type_id_hash) return static_cast<AnchorDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const NPCSpawn *>(ptr);
    if(typeid(NPCSpawn).hash_code() == type_id_hash) return c;
    if(typeid(AnchorDataBase).hash_code() == type_id_hash) return static_cast<const AnchorDataBase *>(c);
    return nullptr;
  }

};

namespace StormReflFileInfo
{
  struct NPCSpawn
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct NPCSpawn::type_info<0>
  {
    using type = ::NPCSpawn;
  };

}

