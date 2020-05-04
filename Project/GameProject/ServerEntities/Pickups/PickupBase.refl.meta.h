#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "PickupBase.refl.h"
#include "Game/ServerEntities/GameServerEntityBase.refl.meta.h"
#include "Runtime/ServerEntity/ServerEntityInitData.refl.meta.h"


template <>
struct StormReflTypeInfo<PickupBaseInitData>
{
  using MyBase = GameServerEntityBaseInitData;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PickupBaseInitData"; }
  static constexpr auto GetNameHash() { return 0x1DE2A467; }
  static constexpr bool HasDefault() { return true; }
  static PickupBaseInitData & GetDefault() { static PickupBaseInitData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PickupBaseInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xA871EE85 == type_name_hash) return static_cast<GameServerEntityBaseInitData *>(c);
    if(0xBEB50F64 == type_name_hash) return static_cast<ServerEntityInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PickupBaseInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xA871EE85 == type_name_hash) return static_cast<const GameServerEntityBaseInitData *>(c);
    if(0xBEB50F64 == type_name_hash) return static_cast<const ServerEntityInitData *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PickupBaseInitData *>(ptr);
    if(typeid(PickupBaseInitData).hash_code() == type_id_hash) return c;
    if(typeid(GameServerEntityBaseInitData).hash_code() == type_id_hash) return static_cast<GameServerEntityBaseInitData *>(c);
    if(typeid(ServerEntityInitData).hash_code() == type_id_hash) return static_cast<ServerEntityInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PickupBaseInitData *>(ptr);
    if(typeid(PickupBaseInitData).hash_code() == type_id_hash) return c;
    if(typeid(GameServerEntityBaseInitData).hash_code() == type_id_hash) return static_cast<const GameServerEntityBaseInitData *>(c);
    if(typeid(ServerEntityInitData).hash_code() == type_id_hash) return static_cast<const ServerEntityInitData *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PickupBase>
{
  using MyBase = GameServerEntityBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PickupBase"; }
  static constexpr auto GetNameHash() { return 0x9E749478; }
  static constexpr bool HasDefault() { return true; }
  static PickupBase & GetDefault() { static PickupBase def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PickupBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x9C1EDB94 == type_name_hash) return static_cast<GameServerEntityBase *>(c);
    if(0x3B0C1433 == type_name_hash) return static_cast<ServerEntity *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PickupBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x9C1EDB94 == type_name_hash) return static_cast<const GameServerEntityBase *>(c);
    if(0x3B0C1433 == type_name_hash) return static_cast<const ServerEntity *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PickupBase *>(ptr);
    if(typeid(PickupBase).hash_code() == type_id_hash) return c;
    if(typeid(GameServerEntityBase).hash_code() == type_id_hash) return static_cast<GameServerEntityBase *>(c);
    if(typeid(ServerEntity).hash_code() == type_id_hash) return static_cast<ServerEntity *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PickupBase *>(ptr);
    if(typeid(PickupBase).hash_code() == type_id_hash) return c;
    if(typeid(GameServerEntityBase).hash_code() == type_id_hash) return static_cast<const GameServerEntityBase *>(c);
    if(typeid(ServerEntity).hash_code() == type_id_hash) return static_cast<const ServerEntity *>(c);
    return nullptr;
  }

};

template <>
struct StormReflFuncInfo<PickupBase>
{
  using MyBase = GameServerEntityBase;
  static constexpr int funcs_n = 0 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};

namespace StormReflFileInfo
{
  struct PickupBase
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct PickupBase::type_info<0>
  {
    using type = ::PickupBaseInitData;
  };

  template <>
  struct PickupBase::type_info<1>
  {
    using type = ::PickupBase;
  };

}

