#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "PlayerServerObject.refl.h"
#include "Game/ServerObjects/GameServerObjectBase.refl.meta.h"
#include "Game/ServerObjects/Player/States/PlayerStateBase.refl.meta.h"
#include "Game/Data/DealDamageAnimationEvent.refl.meta.h"
#include "Game/ServerObjects/Player/PlayerConfig.refl.meta.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.meta.h"


template <>
struct StormReflEnumInfo<PlayerUpgrade>
{
  static constexpr int elems_n = 12;
  static constexpr auto GetName() { return "PlayerUpgrade"; }
  static constexpr auto GetNameHash() { return 0xAD96772E; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<PlayerUpgrade>::elems<0>
{
  static constexpr auto GetName() { return "kDamage1"; }
  static constexpr auto GetNameHash() { return 0x7DBB8FF6; }
  static constexpr auto GetValue() { return PlayerUpgrade::kDamage1; }
};

template <>
struct StormReflEnumInfo<PlayerUpgrade>::elems<1>
{
  static constexpr auto GetName() { return "kDamage2"; }
  static constexpr auto GetNameHash() { return 0xE4B2DE4C; }
  static constexpr auto GetValue() { return PlayerUpgrade::kDamage2; }
};

template <>
struct StormReflEnumInfo<PlayerUpgrade>::elems<2>
{
  static constexpr auto GetName() { return "kAmmo1"; }
  static constexpr auto GetNameHash() { return 0x8C9A2F3C; }
  static constexpr auto GetValue() { return PlayerUpgrade::kAmmo1; }
};

template <>
struct StormReflEnumInfo<PlayerUpgrade>::elems<3>
{
  static constexpr auto GetName() { return "kAmmo2"; }
  static constexpr auto GetNameHash() { return 0x15937E86; }
  static constexpr auto GetValue() { return PlayerUpgrade::kAmmo2; }
};

template <>
struct StormReflEnumInfo<PlayerUpgrade>::elems<4>
{
  static constexpr auto GetName() { return "kHealth1"; }
  static constexpr auto GetNameHash() { return 0xBDDEF12C; }
  static constexpr auto GetValue() { return PlayerUpgrade::kHealth1; }
};

template <>
struct StormReflEnumInfo<PlayerUpgrade>::elems<5>
{
  static constexpr auto GetName() { return "kHealth2"; }
  static constexpr auto GetNameHash() { return 0x24D7A096; }
  static constexpr auto GetValue() { return PlayerUpgrade::kHealth2; }
};

template <>
struct StormReflEnumInfo<PlayerUpgrade>::elems<6>
{
  static constexpr auto GetName() { return "kSpeed1"; }
  static constexpr auto GetNameHash() { return 0x75BEFD94; }
  static constexpr auto GetValue() { return PlayerUpgrade::kSpeed1; }
};

template <>
struct StormReflEnumInfo<PlayerUpgrade>::elems<7>
{
  static constexpr auto GetName() { return "kLife1"; }
  static constexpr auto GetNameHash() { return 0x0DD27BB1; }
  static constexpr auto GetValue() { return PlayerUpgrade::kLife1; }
};

template <>
struct StormReflEnumInfo<PlayerUpgrade>::elems<8>
{
  static constexpr auto GetName() { return "kLife2"; }
  static constexpr auto GetNameHash() { return 0x94DB2A0B; }
  static constexpr auto GetValue() { return PlayerUpgrade::kLife2; }
};

template <>
struct StormReflEnumInfo<PlayerUpgrade>::elems<9>
{
  static constexpr auto GetName() { return "kLife3"; }
  static constexpr auto GetNameHash() { return 0xE3DC1A9D; }
  static constexpr auto GetValue() { return PlayerUpgrade::kLife3; }
};

template <>
struct StormReflEnumInfo<PlayerUpgrade>::elems<10>
{
  static constexpr auto GetName() { return "kRate1"; }
  static constexpr auto GetNameHash() { return 0x08140DA3; }
  static constexpr auto GetValue() { return PlayerUpgrade::kRate1; }
};

template <>
struct StormReflEnumInfo<PlayerUpgrade>::elems<11>
{
  static constexpr auto GetName() { return "kRate2"; }
  static constexpr auto GetNameHash() { return 0x911D5C19; }
  static constexpr auto GetValue() { return PlayerUpgrade::kRate2; }
};

template <>
struct StormReflTypeInfo<PlayerServerObjectInitData>
{
  using MyBase = GameServerObjectBaseInitData;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlayerServerObjectInitData"; }
  static constexpr auto GetNameHash() { return 0x3EDBCEE8; }
  static constexpr bool HasDefault() { return true; }
  static PlayerServerObjectInitData & GetDefault() { static PlayerServerObjectInitData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlayerServerObjectInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xE8EFD458 == type_name_hash) return static_cast<GameServerObjectBaseInitData *>(c);
    if(0x2D36BDE7 == type_name_hash) return static_cast<ServerObjectInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerServerObjectInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xE8EFD458 == type_name_hash) return static_cast<const GameServerObjectBaseInitData *>(c);
    if(0x2D36BDE7 == type_name_hash) return static_cast<const ServerObjectInitData *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlayerServerObjectInitData *>(ptr);
    if(typeid(PlayerServerObjectInitData).hash_code() == type_id_hash) return c;
    if(typeid(GameServerObjectBaseInitData).hash_code() == type_id_hash) return static_cast<GameServerObjectBaseInitData *>(c);
    if(typeid(ServerObjectInitData).hash_code() == type_id_hash) return static_cast<ServerObjectInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerServerObjectInitData *>(ptr);
    if(typeid(PlayerServerObjectInitData).hash_code() == type_id_hash) return c;
    if(typeid(GameServerObjectBaseInitData).hash_code() == type_id_hash) return static_cast<const GameServerObjectBaseInitData *>(c);
    if(typeid(ServerObjectInitData).hash_code() == type_id_hash) return static_cast<const ServerObjectInitData *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlayerServerObject>
{
  using MyBase = GameServerObjectBase;
  static constexpr int fields_n = 20 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlayerServerObject"; }
  static constexpr auto GetNameHash() { return 0xC64518EC; }
  static constexpr bool HasDefault() { return true; }
  static PlayerServerObject & GetDefault() { static PlayerServerObject def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlayerServerObject *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x25DA07B6 == type_name_hash) return static_cast<GameServerObjectBase *>(c);
    if(0x9D89FBB7 == type_name_hash) return static_cast<ServerObject *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerServerObject *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x25DA07B6 == type_name_hash) return static_cast<const GameServerObjectBase *>(c);
    if(0x9D89FBB7 == type_name_hash) return static_cast<const ServerObject *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlayerServerObject *>(ptr);
    if(typeid(PlayerServerObject).hash_code() == type_id_hash) return c;
    if(typeid(GameServerObjectBase).hash_code() == type_id_hash) return static_cast<GameServerObjectBase *>(c);
    if(typeid(ServerObject).hash_code() == type_id_hash) return static_cast<ServerObject *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerServerObject *>(ptr);
    if(typeid(PlayerServerObject).hash_code() == type_id_hash) return c;
    if(typeid(GameServerObjectBase).hash_code() == type_id_hash) return static_cast<const GameServerObjectBase *>(c);
    if(typeid(ServerObject).hash_code() == type_id_hash) return static_cast<const ServerObject *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<0 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = GameNetVec2; // IntersectionVecType<NetFixedPoint<long, 32, 16> >
  static constexpr auto GetName() { return "m_Velocity"; }
  static constexpr auto GetType() { return "IntersectionVecType<NetFixedPoint<long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x48F40287; }
  static constexpr unsigned GetTypeNameHash() { return 0x0D719CFC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_Velocity; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerServerObject *>(obj); return &ptr->m_Velocity; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerServerObject *>(obj); return &ptr->m_Velocity; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<0 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<0 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameNetVec2> & Get() { return self.m_Velocity; }
  std::add_const_t<std::remove_reference_t<GameNetVec2>> & Get() const { return self.m_Velocity; }
  void SetDefault() { self.m_Velocity = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_Velocity; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<1 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = NetRangedNumber<int, -1, 30>; // NetRangedNumber<int, -1, 30>
  static constexpr auto GetName() { return "m_AnimIndex"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, -1, 30>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9984B871; }
  static constexpr unsigned GetTypeNameHash() { return 0xB3BD22BD; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_AnimIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerServerObject *>(obj); return &ptr->m_AnimIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerServerObject *>(obj); return &ptr->m_AnimIndex; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<1 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<1 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, -1, 30>> & Get() { return self.m_AnimIndex; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, -1, 30>>> & Get() const { return self.m_AnimIndex; }
  void SetDefault() { self.m_AnimIndex = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_AnimIndex; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<2 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = NetRangedNumber<int, 0, 31>; // NetRangedNumber<int, 0, 31>
  static constexpr auto GetName() { return "m_AnimFrame"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 31>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAC0FE3BD; }
  static constexpr unsigned GetTypeNameHash() { return 0x72324C82; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_AnimFrame; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerServerObject *>(obj); return &ptr->m_AnimFrame; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerServerObject *>(obj); return &ptr->m_AnimFrame; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<2 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<2 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, 31>> & Get() { return self.m_AnimFrame; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, 31>>> & Get() const { return self.m_AnimFrame; }
  void SetDefault() { self.m_AnimFrame = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_AnimFrame; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<3 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = NetRangedNumber<int, 0, 63>; // NetRangedNumber<int, 0, 63>
  static constexpr auto GetName() { return "m_AnimDelay"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 63>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAB6D5FEB; }
  static constexpr unsigned GetTypeNameHash() { return 0x46CFECEB; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_AnimDelay; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerServerObject *>(obj); return &ptr->m_AnimDelay; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerServerObject *>(obj); return &ptr->m_AnimDelay; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<3 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<3 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, 63>> & Get() { return self.m_AnimDelay; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, 63>>> & Get() const { return self.m_AnimDelay; }
  void SetDefault() { self.m_AnimDelay = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_AnimDelay; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<4 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = NetEnum<CharacterFacing>; // NetEnum<CharacterFacing>
  static constexpr auto GetName() { return "m_Facing"; }
  static constexpr auto GetType() { return "NetEnum<CharacterFacing>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC03F5E41; }
  static constexpr unsigned GetTypeNameHash() { return 0x94981591; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_Facing; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerServerObject *>(obj); return &ptr->m_Facing; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerServerObject *>(obj); return &ptr->m_Facing; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<4 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<4 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetEnum<CharacterFacing>> & Get() { return self.m_Facing; }
  std::add_const_t<std::remove_reference_t<NetEnum<CharacterFacing>>> & Get() const { return self.m_Facing; }
  void SetDefault() { self.m_Facing = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_Facing; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<5 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = NetRangedNumber<int, 0, 31>; // NetRangedNumber<int, 0, 31>
  static constexpr auto GetName() { return "m_AttackId"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 31>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA5FC6351; }
  static constexpr unsigned GetTypeNameHash() { return 0x72324C82; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_AttackId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerServerObject *>(obj); return &ptr->m_AttackId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerServerObject *>(obj); return &ptr->m_AttackId; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<5 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<5 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, 31>> & Get() { return self.m_AttackId; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, 31>>> & Get() const { return self.m_AttackId; }
  void SetDefault() { self.m_AttackId = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_AttackId; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<6 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Invulnerable"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x91D2B6B5; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_Invulnerable; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerServerObject *>(obj); return &ptr->m_Invulnerable; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerServerObject *>(obj); return &ptr->m_Invulnerable; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<6 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<6 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Invulnerable; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Invulnerable; }
  void SetDefault() { self.m_Invulnerable = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_Invulnerable; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<7 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = NetRangedNumber<int, 0, 20>; // NetRangedNumber<int, 0, 20>
  static constexpr auto GetName() { return "m_RefireTime"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 20>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7C0B0C6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x6AEB17F4; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_RefireTime; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerServerObject *>(obj); return &ptr->m_RefireTime; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerServerObject *>(obj); return &ptr->m_RefireTime; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<7 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<7 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, 20>> & Get() { return self.m_RefireTime; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, 20>>> & Get() const { return self.m_RefireTime; }
  void SetDefault() { self.m_RefireTime = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_RefireTime; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<8 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = NetRangedNumber<int, 0, 30>; // NetRangedNumber<int, 0, 30>
  static constexpr auto GetName() { return "m_Ammo"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 30>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD112EB35; }
  static constexpr unsigned GetTypeNameHash() { return 0x6B297DC3; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 8 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_Ammo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerServerObject *>(obj); return &ptr->m_Ammo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerServerObject *>(obj); return &ptr->m_Ammo; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<8 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<8 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, 30>> & Get() { return self.m_Ammo; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, 30>>> & Get() const { return self.m_Ammo; }
  void SetDefault() { self.m_Ammo = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_Ammo; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<9 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = ClientInput; // ClientInput
  static constexpr auto GetName() { return "m_Input"; }
  static constexpr auto GetType() { return "ClientInput"; }
  static constexpr unsigned GetFieldNameHash() { return 0x551EA2B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x13CC217D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 9 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_Input; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerServerObject *>(obj); return &ptr->m_Input; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerServerObject *>(obj); return &ptr->m_Input; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<9 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<9 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ClientInput> & Get() { return self.m_Input; }
  std::add_const_t<std::remove_reference_t<ClientInput>> & Get() const { return self.m_Input; }
  void SetDefault() { self.m_Input = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_Input; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<10 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = NetPolymorphic<PlayerStateBase>; // NetPolymorphic<PlayerStateBase>
  static constexpr auto GetName() { return "m_State"; }
  static constexpr auto GetType() { return "NetPolymorphic<PlayerStateBase>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2EA5429B; }
  static constexpr unsigned GetTypeNameHash() { return 0x44373E80; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 10 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_State; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerServerObject *>(obj); return &ptr->m_State; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerServerObject *>(obj); return &ptr->m_State; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<10 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<10 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetPolymorphic<PlayerStateBase>> & Get() { return self.m_State; }
  std::add_const_t<std::remove_reference_t<NetPolymorphic<PlayerStateBase>>> & Get() const { return self.m_State; }
  void SetDefault() { self.m_State = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_State; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<11 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = PlayerConfigPtr; // NetReflectionStaticListPtr<ConfigPtr<PlayerConfig>, &g_PlayerConfig, &g_PlayerConfigCount, true>
  static constexpr auto GetName() { return "m_Config"; }
  static constexpr auto GetType() { return "NetReflectionStaticListPtr<ConfigPtr<PlayerConfig>, &g_PlayerConfig, &g_PlayerConfigCount, true>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x99B578B4; }
  static constexpr unsigned GetTypeNameHash() { return 0xE109CB64; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 11 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_Config; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerServerObject *>(obj); return &ptr->m_Config; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerServerObject *>(obj); return &ptr->m_Config; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<11 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<11 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, PlayerConfigPtr> & Get() { return self.m_Config; }
  std::add_const_t<std::remove_reference_t<PlayerConfigPtr>> & Get() const { return self.m_Config; }
  void SetDefault() { self.m_Config = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_Config; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<12 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Bat"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6C7EED78; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 12 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_Bat; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerServerObject *>(obj); return &ptr->m_Bat; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerServerObject *>(obj); return &ptr->m_Bat; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<12 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<12 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Bat; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Bat; }
  void SetDefault() { self.m_Bat = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_Bat; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<13 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = NetRangedNumber<int, 0, kMaxBatTimer>; // NetRangedNumber<int, 0, 300>
  static constexpr auto GetName() { return "m_BatTimer"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 300>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD181A204; }
  static constexpr unsigned GetTypeNameHash() { return 0x8FE665DF; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 13 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_BatTimer; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerServerObject *>(obj); return &ptr->m_BatTimer; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerServerObject *>(obj); return &ptr->m_BatTimer; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<13 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<13 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, kMaxBatTimer>> & Get() { return self.m_BatTimer; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, kMaxBatTimer>>> & Get() const { return self.m_BatTimer; }
  void SetDefault() { self.m_BatTimer = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_BatTimer; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<14 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = NetRangedNumber<int, 0, kAbsoluteMaxHealth>; // NetRangedNumber<int, 0, 12>
  static constexpr auto GetName() { return "m_Health"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 12>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x83E574DB; }
  static constexpr unsigned GetTypeNameHash() { return 0x5A9BCB2F; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 14 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_Health; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerServerObject *>(obj); return &ptr->m_Health; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerServerObject *>(obj); return &ptr->m_Health; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<14 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<14 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, kAbsoluteMaxHealth>> & Get() { return self.m_Health; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, kAbsoluteMaxHealth>>> & Get() const { return self.m_Health; }
  void SetDefault() { self.m_Health = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_Health; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<15 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = NetRangedNumber<int, 0, kMaxLives>; // NetRangedNumber<int, 0, 5>
  static constexpr auto GetName() { return "m_Lives"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 5>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD002EE3E; }
  static constexpr unsigned GetTypeNameHash() { return 0xFCA4CDC9; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 15 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_Lives; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerServerObject *>(obj); return &ptr->m_Lives; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerServerObject *>(obj); return &ptr->m_Lives; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<15 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<15 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, kMaxLives>> & Get() { return self.m_Lives; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, kMaxLives>>> & Get() const { return self.m_Lives; }
  void SetDefault() { self.m_Lives = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_Lives; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<16 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = ServerObjectHandle; // ServerObjectHandle
  static constexpr auto GetName() { return "m_NPCBeingEaten"; }
  static constexpr auto GetType() { return "ServerObjectHandle"; }
  static constexpr unsigned GetFieldNameHash() { return 0x53500748; }
  static constexpr unsigned GetTypeNameHash() { return 0xCB9DB57C; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 16 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_NPCBeingEaten; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerServerObject *>(obj); return &ptr->m_NPCBeingEaten; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerServerObject *>(obj); return &ptr->m_NPCBeingEaten; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<16 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<16 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ServerObjectHandle> & Get() { return self.m_NPCBeingEaten; }
  std::add_const_t<std::remove_reference_t<ServerObjectHandle>> & Get() const { return self.m_NPCBeingEaten; }
  void SetDefault() { self.m_NPCBeingEaten = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_NPCBeingEaten; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<17 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_InCoffin"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x59AF9CCD; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 17 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_InCoffin; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerServerObject *>(obj); return &ptr->m_InCoffin; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerServerObject *>(obj); return &ptr->m_InCoffin; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<17 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<17 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_InCoffin; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_InCoffin; }
  void SetDefault() { self.m_InCoffin = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_InCoffin; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<18 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = NetRangedNumber<int, 0, 64>; // NetRangedNumber<int, 0, 64>
  static constexpr auto GetName() { return "m_FrozenFrames"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 64>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF3953FAD; }
  static constexpr unsigned GetTypeNameHash() { return 0x098E7A2C; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 18 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_FrozenFrames; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerServerObject *>(obj); return &ptr->m_FrozenFrames; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerServerObject *>(obj); return &ptr->m_FrozenFrames; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<18 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<18 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, 64>> & Get() { return self.m_FrozenFrames; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, 64>>> & Get() const { return self.m_FrozenFrames; }
  void SetDefault() { self.m_FrozenFrames = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_FrozenFrames; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<19 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = int16_t; // short
  static constexpr auto GetName() { return "m_Upgrades"; }
  static constexpr auto GetType() { return "short"; }
  static constexpr unsigned GetFieldNameHash() { return 0x10F7842B; }
  static constexpr unsigned GetTypeNameHash() { return 0x8F2890A2; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 19 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_Upgrades; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerServerObject *>(obj); return &ptr->m_Upgrades; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerServerObject *>(obj); return &ptr->m_Upgrades; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<19 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<19 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int16_t> & Get() { return self.m_Upgrades; }
  std::add_const_t<std::remove_reference_t<int16_t>> & Get() const { return self.m_Upgrades; }
  void SetDefault() { self.m_Upgrades = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_Upgrades; }
};

template <>
struct StormReflFuncInfo<PlayerServerObject>
{
  using MyBase = GameServerObjectBase;
  static constexpr int funcs_n = 4 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};

template <>
struct StormReflFuncInfo<PlayerServerObject>::func_data_static<0 + StormReflFuncInfo<GameServerObjectBase>::funcs_n>
{
  using func_ptr_type = bool (PlayerServerObject::*)(const PlaceholderEvent &, const EventMetaData &);
  using return_type = bool;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandlePlaceholderEvent"; }
  static constexpr auto GetReturnType() { return "bool"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xB51A771F; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFunctionIndex() { return 0 + StormReflFuncInfo<GameServerObjectBase>::funcs_n; }
  static constexpr func_ptr_type GetFunctionPtr() { return &PlayerServerObject::HandlePlaceholderEvent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<PlayerServerObject>::func_data_static<0 + StormReflFuncInfo<GameServerObjectBase>::funcs_n>::param_info<0>
{
  using param_type = const PlaceholderEvent &;
  static constexpr auto GetName() { return "ev"; }
  static constexpr auto GetType() { return "const PlaceholderEvent &"; }
  static constexpr unsigned GetNameHash() { return 0xE0355914; }
  static constexpr unsigned GetTypeNameHash() { return 0xB0413EBA; }
};

template <>
struct StormReflFuncInfo<PlayerServerObject>::func_data_static<0 + StormReflFuncInfo<GameServerObjectBase>::funcs_n>::param_info<1>
{
  using param_type = const EventMetaData &;
  static constexpr auto GetName() { return "meta"; }
  static constexpr auto GetType() { return "const EventMetaData &"; }
  static constexpr unsigned GetNameHash() { return 0xD7F21435; }
  static constexpr unsigned GetTypeNameHash() { return 0x039083D7; }
};

template <>
struct StormReflFuncInfo<PlayerServerObject>::func_data_static<1 + StormReflFuncInfo<GameServerObjectBase>::funcs_n>
{
  using func_ptr_type = bool (PlayerServerObject::*)(const DamageEvent &, const EventMetaData &);
  using return_type = bool;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleDamageEvent"; }
  static constexpr auto GetReturnType() { return "bool"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x38A81F11; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFunctionIndex() { return 1 + StormReflFuncInfo<GameServerObjectBase>::funcs_n; }
  static constexpr func_ptr_type GetFunctionPtr() { return &PlayerServerObject::HandleDamageEvent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<PlayerServerObject>::func_data_static<1 + StormReflFuncInfo<GameServerObjectBase>::funcs_n>::param_info<0>
{
  using param_type = const DamageEvent &;
  static constexpr auto GetName() { return "ev"; }
  static constexpr auto GetType() { return "const DamageEvent &"; }
  static constexpr unsigned GetNameHash() { return 0xE0355914; }
  static constexpr unsigned GetTypeNameHash() { return 0x18F056E3; }
};

template <>
struct StormReflFuncInfo<PlayerServerObject>::func_data_static<1 + StormReflFuncInfo<GameServerObjectBase>::funcs_n>::param_info<1>
{
  using param_type = const EventMetaData &;
  static constexpr auto GetName() { return "meta"; }
  static constexpr auto GetType() { return "const EventMetaData &"; }
  static constexpr unsigned GetNameHash() { return 0xD7F21435; }
  static constexpr unsigned GetTypeNameHash() { return 0x039083D7; }
};

template <>
struct StormReflFuncInfo<PlayerServerObject>::func_data_static<2 + StormReflFuncInfo<GameServerObjectBase>::funcs_n>
{
  using func_ptr_type = bool (PlayerServerObject::*)(const DealDamageAnimationEvent &, const EventMetaData &);
  using return_type = bool;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleDealDamageEvent"; }
  static constexpr auto GetReturnType() { return "bool"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x197B96A4; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFunctionIndex() { return 2 + StormReflFuncInfo<GameServerObjectBase>::funcs_n; }
  static constexpr func_ptr_type GetFunctionPtr() { return &PlayerServerObject::HandleDealDamageEvent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<PlayerServerObject>::func_data_static<2 + StormReflFuncInfo<GameServerObjectBase>::funcs_n>::param_info<0>
{
  using param_type = const DealDamageAnimationEvent &;
  static constexpr auto GetName() { return "ev"; }
  static constexpr auto GetType() { return "const DealDamageAnimationEvent &"; }
  static constexpr unsigned GetNameHash() { return 0xE0355914; }
  static constexpr unsigned GetTypeNameHash() { return 0x558C63ED; }
};

template <>
struct StormReflFuncInfo<PlayerServerObject>::func_data_static<2 + StormReflFuncInfo<GameServerObjectBase>::funcs_n>::param_info<1>
{
  using param_type = const EventMetaData &;
  static constexpr auto GetName() { return "meta"; }
  static constexpr auto GetType() { return "const EventMetaData &"; }
  static constexpr unsigned GetNameHash() { return 0xD7F21435; }
  static constexpr unsigned GetTypeNameHash() { return 0x039083D7; }
};

template <>
struct StormReflFuncInfo<PlayerServerObject>::func_data_static<3 + StormReflFuncInfo<GameServerObjectBase>::funcs_n>
{
  using func_ptr_type = bool (PlayerServerObject::*)(const PickupAvailableEvent &, const EventMetaData &);
  using return_type = bool;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandlePickupAvailableEvent"; }
  static constexpr auto GetReturnType() { return "bool"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x08F1EBDE; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFunctionIndex() { return 3 + StormReflFuncInfo<GameServerObjectBase>::funcs_n; }
  static constexpr func_ptr_type GetFunctionPtr() { return &PlayerServerObject::HandlePickupAvailableEvent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<PlayerServerObject>::func_data_static<3 + StormReflFuncInfo<GameServerObjectBase>::funcs_n>::param_info<0>
{
  using param_type = const PickupAvailableEvent &;
  static constexpr auto GetName() { return "ev"; }
  static constexpr auto GetType() { return "const PickupAvailableEvent &"; }
  static constexpr unsigned GetNameHash() { return 0xE0355914; }
  static constexpr unsigned GetTypeNameHash() { return 0xCCE26520; }
};

template <>
struct StormReflFuncInfo<PlayerServerObject>::func_data_static<3 + StormReflFuncInfo<GameServerObjectBase>::funcs_n>::param_info<1>
{
  using param_type = const EventMetaData &;
  static constexpr auto GetName() { return "meta"; }
  static constexpr auto GetType() { return "const EventMetaData &"; }
  static constexpr unsigned GetNameHash() { return 0xD7F21435; }
  static constexpr unsigned GetTypeNameHash() { return 0x039083D7; }
};

namespace StormReflFileInfo
{
  struct PlayerServerObject
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct PlayerServerObject::type_info<0>
  {
    using type = ::PlayerServerObjectInitData;
  };

  template <>
  struct PlayerServerObject::type_info<1>
  {
    using type = ::PlayerServerObject;
  };

}

