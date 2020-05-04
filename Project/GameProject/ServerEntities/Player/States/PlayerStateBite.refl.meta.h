#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "PlayerStateBite.refl.h"
#include "Game/ServerEntities/Player/States/PlayerStateBase.refl.meta.h"


template <>
struct StormReflTypeInfo<PlayerStateBite>
{
  using MyBase = PlayerStateBase;
  static constexpr int fields_n = 1 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlayerStateBite"; }
  static constexpr auto GetNameHash() { return 0xC92E75EE; }
  static constexpr bool HasDefault() { return true; }
  static PlayerStateBite & GetDefault() { static PlayerStateBite def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlayerStateBite *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x887CB291 == type_name_hash) return static_cast<PlayerStateBase *>(c);
    if(0x8FB16778 == type_name_hash) return static_cast<PlayerStateEventHandler<PlayerStateBite> *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerStateBite *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x887CB291 == type_name_hash) return static_cast<const PlayerStateBase *>(c);
    if(0x8FB16778 == type_name_hash) return static_cast<const PlayerStateEventHandler<PlayerStateBite> *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlayerStateBite *>(ptr);
    if(typeid(PlayerStateBite).hash_code() == type_id_hash) return c;
    if(typeid(PlayerStateBase).hash_code() == type_id_hash) return static_cast<PlayerStateBase *>(c);
    if(typeid(PlayerStateEventHandler<PlayerStateBite>).hash_code() == type_id_hash) return static_cast<PlayerStateEventHandler<PlayerStateBite> *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerStateBite *>(ptr);
    if(typeid(PlayerStateBite).hash_code() == type_id_hash) return c;
    if(typeid(PlayerStateBase).hash_code() == type_id_hash) return static_cast<const PlayerStateBase *>(c);
    if(typeid(PlayerStateEventHandler<PlayerStateBite>).hash_code() == type_id_hash) return static_cast<const PlayerStateEventHandler<PlayerStateBite> *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlayerStateBite>::field_data_static<0 + StormReflTypeInfo<PlayerStateBase>::fields_n>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Finished"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x50637F12; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<PlayerStateBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerStateBite::m_Finished; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerStateBite *>(obj); return &ptr->m_Finished; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerStateBite *>(obj); return &ptr->m_Finished; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerStateBite>::field_data<0 + StormReflTypeInfo<PlayerStateBase>::fields_n, Self> : public StormReflTypeInfo<PlayerStateBite>::field_data_static<0 + StormReflTypeInfo<PlayerStateBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Finished; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Finished; }
  void SetDefault() { self.m_Finished = StormReflTypeInfo<PlayerStateBite>::GetDefault().m_Finished; }
};

template <>
struct StormReflFuncInfo<PlayerStateBite>
{
  using MyBase = PlayerStateBase;
  static constexpr int funcs_n = 0 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};

namespace StormReflFileInfo
{
  struct PlayerStateBite
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct PlayerStateBite::type_info<0>
  {
    using type = ::PlayerStateBite;
  };

}

