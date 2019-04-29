#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "HealthPickup.refl.h"
#include "Game/ServerObjects/Pickups/PickupBase.refl.meta.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.meta.h"


template <>
struct StormReflTypeInfo<HealthPickupInitData>
{
  using MyBase = PickupBaseInitData;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "HealthPickupInitData"; }
  static constexpr auto GetNameHash() { return 0x1A9481BF; }
  static constexpr bool HasDefault() { return true; }
  static HealthPickupInitData & GetDefault() { static HealthPickupInitData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<HealthPickupInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x1DE2A467 == type_name_hash) return static_cast<PickupBaseInitData *>(c);
    if(0xE8EFD458 == type_name_hash) return static_cast<GameServerObjectBaseInitData *>(c);
    if(0x2D36BDE7 == type_name_hash) return static_cast<ServerObjectInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const HealthPickupInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x1DE2A467 == type_name_hash) return static_cast<const PickupBaseInitData *>(c);
    if(0xE8EFD458 == type_name_hash) return static_cast<const GameServerObjectBaseInitData *>(c);
    if(0x2D36BDE7 == type_name_hash) return static_cast<const ServerObjectInitData *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<HealthPickupInitData *>(ptr);
    if(typeid(HealthPickupInitData).hash_code() == type_id_hash) return c;
    if(typeid(PickupBaseInitData).hash_code() == type_id_hash) return static_cast<PickupBaseInitData *>(c);
    if(typeid(GameServerObjectBaseInitData).hash_code() == type_id_hash) return static_cast<GameServerObjectBaseInitData *>(c);
    if(typeid(ServerObjectInitData).hash_code() == type_id_hash) return static_cast<ServerObjectInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const HealthPickupInitData *>(ptr);
    if(typeid(HealthPickupInitData).hash_code() == type_id_hash) return c;
    if(typeid(PickupBaseInitData).hash_code() == type_id_hash) return static_cast<const PickupBaseInitData *>(c);
    if(typeid(GameServerObjectBaseInitData).hash_code() == type_id_hash) return static_cast<const GameServerObjectBaseInitData *>(c);
    if(typeid(ServerObjectInitData).hash_code() == type_id_hash) return static_cast<const ServerObjectInitData *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<HealthPickup>
{
  using MyBase = PickupBase;
  static constexpr int fields_n = 1 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "HealthPickup"; }
  static constexpr auto GetNameHash() { return 0x8FF82065; }
  static constexpr bool HasDefault() { return true; }
  static HealthPickup & GetDefault() { static HealthPickup def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<HealthPickup *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x9E749478 == type_name_hash) return static_cast<PickupBase *>(c);
    if(0x25DA07B6 == type_name_hash) return static_cast<GameServerObjectBase *>(c);
    if(0x9D89FBB7 == type_name_hash) return static_cast<ServerObject *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const HealthPickup *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x9E749478 == type_name_hash) return static_cast<const PickupBase *>(c);
    if(0x25DA07B6 == type_name_hash) return static_cast<const GameServerObjectBase *>(c);
    if(0x9D89FBB7 == type_name_hash) return static_cast<const ServerObject *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<HealthPickup *>(ptr);
    if(typeid(HealthPickup).hash_code() == type_id_hash) return c;
    if(typeid(PickupBase).hash_code() == type_id_hash) return static_cast<PickupBase *>(c);
    if(typeid(GameServerObjectBase).hash_code() == type_id_hash) return static_cast<GameServerObjectBase *>(c);
    if(typeid(ServerObject).hash_code() == type_id_hash) return static_cast<ServerObject *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const HealthPickup *>(ptr);
    if(typeid(HealthPickup).hash_code() == type_id_hash) return c;
    if(typeid(PickupBase).hash_code() == type_id_hash) return static_cast<const PickupBase *>(c);
    if(typeid(GameServerObjectBase).hash_code() == type_id_hash) return static_cast<const GameServerObjectBase *>(c);
    if(typeid(ServerObject).hash_code() == type_id_hash) return static_cast<const ServerObject *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<HealthPickup>::field_data_static<0 + StormReflTypeInfo<PickupBase>::fields_n>
{
  using member_type = ServerObjectHandle; // ServerObjectHandle
  static constexpr auto GetName() { return "m_AvoidObject"; }
  static constexpr auto GetType() { return "ServerObjectHandle"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC9919845; }
  static constexpr unsigned GetTypeNameHash() { return 0xCB9DB57C; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<PickupBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &HealthPickup::m_AvoidObject; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<HealthPickup *>(obj); return &ptr->m_AvoidObject; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const HealthPickup *>(obj); return &ptr->m_AvoidObject; }
};

template <typename Self>
struct StormReflTypeInfo<HealthPickup>::field_data<0 + StormReflTypeInfo<PickupBase>::fields_n, Self> : public StormReflTypeInfo<HealthPickup>::field_data_static<0 + StormReflTypeInfo<PickupBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ServerObjectHandle> & Get() { return self.m_AvoidObject; }
  std::add_const_t<std::remove_reference_t<ServerObjectHandle>> & Get() const { return self.m_AvoidObject; }
  void SetDefault() { self.m_AvoidObject = StormReflTypeInfo<HealthPickup>::GetDefault().m_AvoidObject; }
};

template <>
struct StormReflFuncInfo<HealthPickup>
{
  using MyBase = PickupBase;
  static constexpr int funcs_n = 0 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};

namespace StormReflFileInfo
{
  struct HealthPickup
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct HealthPickup::type_info<0>
  {
    using type = ::HealthPickupInitData;
  };

  template <>
  struct HealthPickup::type_info<1>
  {
    using type = ::HealthPickup;
  };

}

