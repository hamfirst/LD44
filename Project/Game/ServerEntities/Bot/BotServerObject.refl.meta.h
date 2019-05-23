#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "BotServerObject.refl.h"
#include "Game/ServerEntities/CharacterFacing.refl.meta.h"
#include "Game/ServerEntities/GameServerEntityBase.refl.meta.h"
#include "Runtime/ServerEntity/ServerEntityInitData.refl.meta.h"


template <>
struct StormReflTypeInfo<BotServerObjectInitData>
{
  using MyBase = GameServerEntityBaseInitData;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "BotServerObjectInitData"; }
  static constexpr auto GetNameHash() { return 0x1C601FCD; }
  static constexpr bool HasDefault() { return true; }
  static BotServerObjectInitData & GetDefault() { static BotServerObjectInitData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<BotServerObjectInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xA871EE85 == type_name_hash) return static_cast<GameServerEntityBaseInitData *>(c);
    if(0xBEB50F64 == type_name_hash) return static_cast<ServerEntityInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const BotServerObjectInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xA871EE85 == type_name_hash) return static_cast<const GameServerEntityBaseInitData *>(c);
    if(0xBEB50F64 == type_name_hash) return static_cast<const ServerEntityInitData *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<BotServerObjectInitData *>(ptr);
    if(typeid(BotServerObjectInitData).hash_code() == type_id_hash) return c;
    if(typeid(GameServerEntityBaseInitData).hash_code() == type_id_hash) return static_cast<GameServerEntityBaseInitData *>(c);
    if(typeid(ServerEntityInitData).hash_code() == type_id_hash) return static_cast<ServerEntityInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const BotServerObjectInitData *>(ptr);
    if(typeid(BotServerObjectInitData).hash_code() == type_id_hash) return c;
    if(typeid(GameServerEntityBaseInitData).hash_code() == type_id_hash) return static_cast<const GameServerEntityBaseInitData *>(c);
    if(typeid(ServerEntityInitData).hash_code() == type_id_hash) return static_cast<const ServerEntityInitData *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<BotServerObject>
{
  using MyBase = GameServerEntityBase;
  static constexpr int fields_n = 9 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "BotServerObject"; }
  static constexpr auto GetNameHash() { return 0xF3F6D91E; }
  static constexpr bool HasDefault() { return true; }
  static BotServerObject & GetDefault() { static BotServerObject def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<BotServerObject *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x9C1EDB94 == type_name_hash) return static_cast<GameServerEntityBase *>(c);
    if(0x3B0C1433 == type_name_hash) return static_cast<ServerEntity *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const BotServerObject *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x9C1EDB94 == type_name_hash) return static_cast<const GameServerEntityBase *>(c);
    if(0x3B0C1433 == type_name_hash) return static_cast<const ServerEntity *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<BotServerObject *>(ptr);
    if(typeid(BotServerObject).hash_code() == type_id_hash) return c;
    if(typeid(GameServerEntityBase).hash_code() == type_id_hash) return static_cast<GameServerEntityBase *>(c);
    if(typeid(ServerEntity).hash_code() == type_id_hash) return static_cast<ServerEntity *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const BotServerObject *>(ptr);
    if(typeid(BotServerObject).hash_code() == type_id_hash) return c;
    if(typeid(GameServerEntityBase).hash_code() == type_id_hash) return static_cast<const GameServerEntityBase *>(c);
    if(typeid(ServerEntity).hash_code() == type_id_hash) return static_cast<const ServerEntity *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<BotServerObject>::field_data_static<0 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  using member_type = GameNetVec2; // IntersectionVecType<NetFixedPoint<long, 32, 16> >
  static constexpr auto GetName() { return "m_Velocity"; }
  static constexpr auto GetType() { return "IntersectionVecType<NetFixedPoint<long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x48F40287; }
  static constexpr unsigned GetTypeNameHash() { return 0x0D719CFC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<GameServerEntityBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &BotServerObject::m_Velocity; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BotServerObject *>(obj); return &ptr->m_Velocity; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BotServerObject *>(obj); return &ptr->m_Velocity; }
};

template <typename Self>
struct StormReflTypeInfo<BotServerObject>::field_data<0 + StormReflTypeInfo<GameServerEntityBase>::fields_n, Self> : public StormReflTypeInfo<BotServerObject>::field_data_static<0 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameNetVec2> & Get() { return self.m_Velocity; }
  std::add_const_t<std::remove_reference_t<GameNetVec2>> & Get() const { return self.m_Velocity; }
  void SetDefault() { self.m_Velocity = StormReflTypeInfo<BotServerObject>::GetDefault().m_Velocity; }
};

template <>
struct StormReflTypeInfo<BotServerObject>::field_data_static<1 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  using member_type = NetRangedNumber<int, -1, 30>; // NetRangedNumber<int, -1, 30>
  static constexpr auto GetName() { return "m_AnimIndex"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, -1, 30>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9984B871; }
  static constexpr unsigned GetTypeNameHash() { return 0xB3BD22BD; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<GameServerEntityBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &BotServerObject::m_AnimIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BotServerObject *>(obj); return &ptr->m_AnimIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BotServerObject *>(obj); return &ptr->m_AnimIndex; }
};

template <typename Self>
struct StormReflTypeInfo<BotServerObject>::field_data<1 + StormReflTypeInfo<GameServerEntityBase>::fields_n, Self> : public StormReflTypeInfo<BotServerObject>::field_data_static<1 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, -1, 30>> & Get() { return self.m_AnimIndex; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, -1, 30>>> & Get() const { return self.m_AnimIndex; }
  void SetDefault() { self.m_AnimIndex = StormReflTypeInfo<BotServerObject>::GetDefault().m_AnimIndex; }
};

template <>
struct StormReflTypeInfo<BotServerObject>::field_data_static<2 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  using member_type = NetRangedNumber<int, 0, 31>; // NetRangedNumber<int, 0, 31>
  static constexpr auto GetName() { return "m_AnimFrame"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 31>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAC0FE3BD; }
  static constexpr unsigned GetTypeNameHash() { return 0x72324C82; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<GameServerEntityBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &BotServerObject::m_AnimFrame; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BotServerObject *>(obj); return &ptr->m_AnimFrame; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BotServerObject *>(obj); return &ptr->m_AnimFrame; }
};

template <typename Self>
struct StormReflTypeInfo<BotServerObject>::field_data<2 + StormReflTypeInfo<GameServerEntityBase>::fields_n, Self> : public StormReflTypeInfo<BotServerObject>::field_data_static<2 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, 31>> & Get() { return self.m_AnimFrame; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, 31>>> & Get() const { return self.m_AnimFrame; }
  void SetDefault() { self.m_AnimFrame = StormReflTypeInfo<BotServerObject>::GetDefault().m_AnimFrame; }
};

template <>
struct StormReflTypeInfo<BotServerObject>::field_data_static<3 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  using member_type = NetRangedNumber<int, 0, 63>; // NetRangedNumber<int, 0, 63>
  static constexpr auto GetName() { return "m_AnimDelay"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 63>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAB6D5FEB; }
  static constexpr unsigned GetTypeNameHash() { return 0x46CFECEB; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3 + StormReflTypeInfo<GameServerEntityBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &BotServerObject::m_AnimDelay; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BotServerObject *>(obj); return &ptr->m_AnimDelay; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BotServerObject *>(obj); return &ptr->m_AnimDelay; }
};

template <typename Self>
struct StormReflTypeInfo<BotServerObject>::field_data<3 + StormReflTypeInfo<GameServerEntityBase>::fields_n, Self> : public StormReflTypeInfo<BotServerObject>::field_data_static<3 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, 63>> & Get() { return self.m_AnimDelay; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, 63>>> & Get() const { return self.m_AnimDelay; }
  void SetDefault() { self.m_AnimDelay = StormReflTypeInfo<BotServerObject>::GetDefault().m_AnimDelay; }
};

template <>
struct StormReflTypeInfo<BotServerObject>::field_data_static<4 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  using member_type = NetEnum<CharacterFacing>; // NetEnum<CharacterFacing>
  static constexpr auto GetName() { return "m_Facing"; }
  static constexpr auto GetType() { return "NetEnum<CharacterFacing>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC03F5E41; }
  static constexpr unsigned GetTypeNameHash() { return 0x94981591; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4 + StormReflTypeInfo<GameServerEntityBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &BotServerObject::m_Facing; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BotServerObject *>(obj); return &ptr->m_Facing; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BotServerObject *>(obj); return &ptr->m_Facing; }
};

template <typename Self>
struct StormReflTypeInfo<BotServerObject>::field_data<4 + StormReflTypeInfo<GameServerEntityBase>::fields_n, Self> : public StormReflTypeInfo<BotServerObject>::field_data_static<4 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetEnum<CharacterFacing>> & Get() { return self.m_Facing; }
  std::add_const_t<std::remove_reference_t<NetEnum<CharacterFacing>>> & Get() const { return self.m_Facing; }
  void SetDefault() { self.m_Facing = StormReflTypeInfo<BotServerObject>::GetDefault().m_Facing; }
};

template <>
struct StormReflTypeInfo<BotServerObject>::field_data_static<5 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  using member_type = int16_t; // short
  static constexpr auto GetName() { return "m_StateTimer"; }
  static constexpr auto GetType() { return "short"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE86EE10E; }
  static constexpr unsigned GetTypeNameHash() { return 0x8F2890A2; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5 + StormReflTypeInfo<GameServerEntityBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &BotServerObject::m_StateTimer; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BotServerObject *>(obj); return &ptr->m_StateTimer; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BotServerObject *>(obj); return &ptr->m_StateTimer; }
};

template <typename Self>
struct StormReflTypeInfo<BotServerObject>::field_data<5 + StormReflTypeInfo<GameServerEntityBase>::fields_n, Self> : public StormReflTypeInfo<BotServerObject>::field_data_static<5 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int16_t> & Get() { return self.m_StateTimer; }
  std::add_const_t<std::remove_reference_t<int16_t>> & Get() const { return self.m_StateTimer; }
  void SetDefault() { self.m_StateTimer = StormReflTypeInfo<BotServerObject>::GetDefault().m_StateTimer; }
};

template <>
struct StormReflTypeInfo<BotServerObject>::field_data_static<6 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Dead"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD3B8DC3B; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6 + StormReflTypeInfo<GameServerEntityBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &BotServerObject::m_Dead; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BotServerObject *>(obj); return &ptr->m_Dead; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BotServerObject *>(obj); return &ptr->m_Dead; }
};

template <typename Self>
struct StormReflTypeInfo<BotServerObject>::field_data<6 + StormReflTypeInfo<GameServerEntityBase>::fields_n, Self> : public StormReflTypeInfo<BotServerObject>::field_data_static<6 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Dead; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Dead; }
  void SetDefault() { self.m_Dead = StormReflTypeInfo<BotServerObject>::GetDefault().m_Dead; }
};

template <>
struct StormReflTypeInfo<BotServerObject>::field_data_static<7 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_AlertedFrames"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0x84BD3444; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7 + StormReflTypeInfo<GameServerEntityBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &BotServerObject::m_AlertedFrames; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BotServerObject *>(obj); return &ptr->m_AlertedFrames; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BotServerObject *>(obj); return &ptr->m_AlertedFrames; }
};

template <typename Self>
struct StormReflTypeInfo<BotServerObject>::field_data<7 + StormReflTypeInfo<GameServerEntityBase>::fields_n, Self> : public StormReflTypeInfo<BotServerObject>::field_data_static<7 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_AlertedFrames; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_AlertedFrames; }
  void SetDefault() { self.m_AlertedFrames = StormReflTypeInfo<BotServerObject>::GetDefault().m_AlertedFrames; }
};

template <>
struct StormReflTypeInfo<BotServerObject>::field_data_static<8 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_BeingEaten"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x59F876B9; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 8 + StormReflTypeInfo<GameServerEntityBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &BotServerObject::m_BeingEaten; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BotServerObject *>(obj); return &ptr->m_BeingEaten; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BotServerObject *>(obj); return &ptr->m_BeingEaten; }
};

template <typename Self>
struct StormReflTypeInfo<BotServerObject>::field_data<8 + StormReflTypeInfo<GameServerEntityBase>::fields_n, Self> : public StormReflTypeInfo<BotServerObject>::field_data_static<8 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_BeingEaten; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_BeingEaten; }
  void SetDefault() { self.m_BeingEaten = StormReflTypeInfo<BotServerObject>::GetDefault().m_BeingEaten; }
};

template <>
struct StormReflFuncInfo<BotServerObject>
{
  using MyBase = GameServerEntityBase;
  static constexpr int funcs_n = 0 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};

namespace StormReflFileInfo
{
  struct BotServerObject
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct BotServerObject::type_info<0>
  {
    using type = ::BotServerObjectInitData;
  };

  template <>
  struct BotServerObject::type_info<1>
  {
    using type = ::BotServerObject;
  };

}

