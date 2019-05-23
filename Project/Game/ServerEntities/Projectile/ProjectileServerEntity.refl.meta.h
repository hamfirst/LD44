#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "ProjectileServerEntity.refl.h"
#include "Game/ServerEntities/GameServerEntityBase.refl.meta.h"
#include "Game/ServerEntities/Projectile/ProjectileConfig.refl.meta.h"
#include "Game/ServerEntities/Projectile/Motion/ProjectileMotionBase.refl.meta.h"
#include "Runtime/ServerEntity/ServerEntityInitData.refl.meta.h"


template <>
struct StormReflTypeInfo<ProjectileServerEntitySpawnData>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ProjectileServerEntitySpawnData"; }
  static constexpr auto GetNameHash() { return 0x62C1C5FD; }
  static constexpr bool HasDefault() { return true; }
  static ProjectileServerEntitySpawnData & GetDefault() { static ProjectileServerEntitySpawnData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ProjectileServerEntitySpawnData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileServerEntitySpawnData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ProjectileServerEntitySpawnData *>(ptr);
    if(typeid(ProjectileServerEntitySpawnData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileServerEntitySpawnData *>(ptr);
    if(typeid(ProjectileServerEntitySpawnData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ProjectileServerEntitySpawnData>::field_data_static<0>
{
  using member_type = GameNetVec2; // IntersectionVecType<NetFixedPoint<long, 32, 16> >
  static constexpr auto GetName() { return "m_Position"; }
  static constexpr auto GetType() { return "IntersectionVecType<NetFixedPoint<long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB00030DB; }
  static constexpr unsigned GetTypeNameHash() { return 0x0D719CFC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerEntitySpawnData::m_Position; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerEntitySpawnData *>(obj); return &ptr->m_Position; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerEntitySpawnData *>(obj); return &ptr->m_Position; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerEntitySpawnData>::field_data<0, Self> : public StormReflTypeInfo<ProjectileServerEntitySpawnData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameNetVec2> & Get() { return self.m_Position; }
  std::add_const_t<std::remove_reference_t<GameNetVec2>> & Get() const { return self.m_Position; }
  void SetDefault() { self.m_Position = StormReflTypeInfo<ProjectileServerEntitySpawnData>::GetDefault().m_Position; }
};

template <>
struct StormReflTypeInfo<ProjectileServerEntitySpawnData>::field_data_static<1>
{
  using member_type = GameNetVec2; // IntersectionVecType<NetFixedPoint<long, 32, 16> >
  static constexpr auto GetName() { return "m_Direction"; }
  static constexpr auto GetType() { return "IntersectionVecType<NetFixedPoint<long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE26AF0A8; }
  static constexpr unsigned GetTypeNameHash() { return 0x0D719CFC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerEntitySpawnData::m_Direction; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerEntitySpawnData *>(obj); return &ptr->m_Direction; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerEntitySpawnData *>(obj); return &ptr->m_Direction; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerEntitySpawnData>::field_data<1, Self> : public StormReflTypeInfo<ProjectileServerEntitySpawnData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameNetVec2> & Get() { return self.m_Direction; }
  std::add_const_t<std::remove_reference_t<GameNetVec2>> & Get() const { return self.m_Direction; }
  void SetDefault() { self.m_Direction = StormReflTypeInfo<ProjectileServerEntitySpawnData>::GetDefault().m_Direction; }
};

template <>
struct StormReflTypeInfo<ProjectileServerEntitySpawnData>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_TeamIndex"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1156ED7E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerEntitySpawnData::m_TeamIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerEntitySpawnData *>(obj); return &ptr->m_TeamIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerEntitySpawnData *>(obj); return &ptr->m_TeamIndex; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerEntitySpawnData>::field_data<2, Self> : public StormReflTypeInfo<ProjectileServerEntitySpawnData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_TeamIndex; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_TeamIndex; }
  void SetDefault() { self.m_TeamIndex = StormReflTypeInfo<ProjectileServerEntitySpawnData>::GetDefault().m_TeamIndex; }
};

template <>
struct StormReflTypeInfo<ProjectileServerEntitySpawnData>::field_data_static<3>
{
  using member_type = ServerEntityHandle; // ServerEntityHandle
  static constexpr auto GetName() { return "m_OwnerHandle"; }
  static constexpr auto GetType() { return "ServerEntityHandle"; }
  static constexpr unsigned GetFieldNameHash() { return 0x09D2FBB0; }
  static constexpr unsigned GetTypeNameHash() { return 0xE34AD467; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerEntitySpawnData::m_OwnerHandle; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerEntitySpawnData *>(obj); return &ptr->m_OwnerHandle; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerEntitySpawnData *>(obj); return &ptr->m_OwnerHandle; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerEntitySpawnData>::field_data<3, Self> : public StormReflTypeInfo<ProjectileServerEntitySpawnData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ServerEntityHandle> & Get() { return self.m_OwnerHandle; }
  std::add_const_t<std::remove_reference_t<ServerEntityHandle>> & Get() const { return self.m_OwnerHandle; }
  void SetDefault() { self.m_OwnerHandle = StormReflTypeInfo<ProjectileServerEntitySpawnData>::GetDefault().m_OwnerHandle; }
};

template <>
struct StormReflTypeInfo<ProjectileServerEntitySpawnData>::field_data_static<4>
{
  using member_type = const ConfigPtr<ProjectileConfig> *; // const ConfigPtr<ProjectileConfig> *
  static constexpr auto GetName() { return "m_Config"; }
  static constexpr auto GetType() { return "const ConfigPtr<ProjectileConfig> *"; }
  static constexpr unsigned GetFieldNameHash() { return 0x99B578B4; }
  static constexpr unsigned GetTypeNameHash() { return 0x38CD7873; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerEntitySpawnData::m_Config; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerEntitySpawnData *>(obj); return &ptr->m_Config; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerEntitySpawnData *>(obj); return &ptr->m_Config; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerEntitySpawnData>::field_data<4, Self> : public StormReflTypeInfo<ProjectileServerEntitySpawnData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, const ConfigPtr<ProjectileConfig> *> & Get() { return self.m_Config; }
  std::add_const_t<std::remove_reference_t<const ConfigPtr<ProjectileConfig> *>> & Get() const { return self.m_Config; }
  void SetDefault() { self.m_Config = StormReflTypeInfo<ProjectileServerEntitySpawnData>::GetDefault().m_Config; }
};

template <>
struct StormReflTypeInfo<ProjectileServerEntityInitData>
{
  using MyBase = GameServerEntityBaseInitData;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ProjectileServerEntityInitData"; }
  static constexpr auto GetNameHash() { return 0xC9BAA978; }
  static constexpr bool HasDefault() { return true; }
  static ProjectileServerEntityInitData & GetDefault() { static ProjectileServerEntityInitData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ProjectileServerEntityInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xA871EE85 == type_name_hash) return static_cast<GameServerEntityBaseInitData *>(c);
    if(0xBEB50F64 == type_name_hash) return static_cast<ServerEntityInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileServerEntityInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xA871EE85 == type_name_hash) return static_cast<const GameServerEntityBaseInitData *>(c);
    if(0xBEB50F64 == type_name_hash) return static_cast<const ServerEntityInitData *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ProjectileServerEntityInitData *>(ptr);
    if(typeid(ProjectileServerEntityInitData).hash_code() == type_id_hash) return c;
    if(typeid(GameServerEntityBaseInitData).hash_code() == type_id_hash) return static_cast<GameServerEntityBaseInitData *>(c);
    if(typeid(ServerEntityInitData).hash_code() == type_id_hash) return static_cast<ServerEntityInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileServerEntityInitData *>(ptr);
    if(typeid(ProjectileServerEntityInitData).hash_code() == type_id_hash) return c;
    if(typeid(GameServerEntityBaseInitData).hash_code() == type_id_hash) return static_cast<const GameServerEntityBaseInitData *>(c);
    if(typeid(ServerEntityInitData).hash_code() == type_id_hash) return static_cast<const ServerEntityInitData *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ProjectileServerEntity>
{
  using MyBase = GameServerEntityBase;
  static constexpr int fields_n = 8 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ProjectileServerEntity"; }
  static constexpr auto GetNameHash() { return 0xABE30F90; }
  static constexpr bool HasDefault() { return true; }
  static ProjectileServerEntity & GetDefault() { static ProjectileServerEntity def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ProjectileServerEntity *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x9C1EDB94 == type_name_hash) return static_cast<GameServerEntityBase *>(c);
    if(0x3B0C1433 == type_name_hash) return static_cast<ServerEntity *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileServerEntity *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x9C1EDB94 == type_name_hash) return static_cast<const GameServerEntityBase *>(c);
    if(0x3B0C1433 == type_name_hash) return static_cast<const ServerEntity *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ProjectileServerEntity *>(ptr);
    if(typeid(ProjectileServerEntity).hash_code() == type_id_hash) return c;
    if(typeid(GameServerEntityBase).hash_code() == type_id_hash) return static_cast<GameServerEntityBase *>(c);
    if(typeid(ServerEntity).hash_code() == type_id_hash) return static_cast<ServerEntity *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileServerEntity *>(ptr);
    if(typeid(ProjectileServerEntity).hash_code() == type_id_hash) return c;
    if(typeid(GameServerEntityBase).hash_code() == type_id_hash) return static_cast<const GameServerEntityBase *>(c);
    if(typeid(ServerEntity).hash_code() == type_id_hash) return static_cast<const ServerEntity *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ProjectileServerEntity>::field_data_static<0 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  using member_type = GameNetVec2; // IntersectionVecType<NetFixedPoint<long, 32, 16> >
  static constexpr auto GetName() { return "m_Direction"; }
  static constexpr auto GetType() { return "IntersectionVecType<NetFixedPoint<long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE26AF0A8; }
  static constexpr unsigned GetTypeNameHash() { return 0x0D719CFC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<GameServerEntityBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerEntity::m_Direction; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerEntity *>(obj); return &ptr->m_Direction; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerEntity *>(obj); return &ptr->m_Direction; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerEntity>::field_data<0 + StormReflTypeInfo<GameServerEntityBase>::fields_n, Self> : public StormReflTypeInfo<ProjectileServerEntity>::field_data_static<0 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameNetVec2> & Get() { return self.m_Direction; }
  std::add_const_t<std::remove_reference_t<GameNetVec2>> & Get() const { return self.m_Direction; }
  void SetDefault() { self.m_Direction = StormReflTypeInfo<ProjectileServerEntity>::GetDefault().m_Direction; }
};

template <>
struct StormReflTypeInfo<ProjectileServerEntity>::field_data_static<1 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  using member_type = NetRangedNumber<int, -1, kMaxTeams - 1>; // NetRangedNumber<int, -1, 7>
  static constexpr auto GetName() { return "m_Team"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, -1, 7>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFA7D3300; }
  static constexpr unsigned GetTypeNameHash() { return 0x57E60BE3; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<GameServerEntityBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerEntity::m_Team; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerEntity *>(obj); return &ptr->m_Team; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerEntity *>(obj); return &ptr->m_Team; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerEntity>::field_data<1 + StormReflTypeInfo<GameServerEntityBase>::fields_n, Self> : public StormReflTypeInfo<ProjectileServerEntity>::field_data_static<1 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, -1, kMaxTeams - 1>> & Get() { return self.m_Team; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, -1, kMaxTeams - 1>>> & Get() const { return self.m_Team; }
  void SetDefault() { self.m_Team = StormReflTypeInfo<ProjectileServerEntity>::GetDefault().m_Team; }
};

template <>
struct StormReflTypeInfo<ProjectileServerEntity>::field_data_static<2 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  using member_type = ServerEntityHandle; // ServerEntityHandle
  static constexpr auto GetName() { return "m_Owner"; }
  static constexpr auto GetType() { return "ServerEntityHandle"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4256761C; }
  static constexpr unsigned GetTypeNameHash() { return 0xE34AD467; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<GameServerEntityBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerEntity::m_Owner; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerEntity *>(obj); return &ptr->m_Owner; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerEntity *>(obj); return &ptr->m_Owner; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerEntity>::field_data<2 + StormReflTypeInfo<GameServerEntityBase>::fields_n, Self> : public StormReflTypeInfo<ProjectileServerEntity>::field_data_static<2 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ServerEntityHandle> & Get() { return self.m_Owner; }
  std::add_const_t<std::remove_reference_t<ServerEntityHandle>> & Get() const { return self.m_Owner; }
  void SetDefault() { self.m_Owner = StormReflTypeInfo<ProjectileServerEntity>::GetDefault().m_Owner; }
};

template <>
struct StormReflTypeInfo<ProjectileServerEntity>::field_data_static<3 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  using member_type = ProjectileConfigPtr; // NetReflectionStaticListPtr<ConfigPtr<ProjectileConfig>, &g_ProjectileConfigs, &g_ProjectileConfigsCount, true>
  static constexpr auto GetName() { return "m_Config"; }
  static constexpr auto GetType() { return "NetReflectionStaticListPtr<ConfigPtr<ProjectileConfig>, &g_ProjectileConfigs, &g_ProjectileConfigsCount, true>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x99B578B4; }
  static constexpr unsigned GetTypeNameHash() { return 0xA35C1C16; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3 + StormReflTypeInfo<GameServerEntityBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerEntity::m_Config; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerEntity *>(obj); return &ptr->m_Config; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerEntity *>(obj); return &ptr->m_Config; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerEntity>::field_data<3 + StormReflTypeInfo<GameServerEntityBase>::fields_n, Self> : public StormReflTypeInfo<ProjectileServerEntity>::field_data_static<3 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ProjectileConfigPtr> & Get() { return self.m_Config; }
  std::add_const_t<std::remove_reference_t<ProjectileConfigPtr>> & Get() const { return self.m_Config; }
  void SetDefault() { self.m_Config = StormReflTypeInfo<ProjectileServerEntity>::GetDefault().m_Config; }
};

template <>
struct StormReflTypeInfo<ProjectileServerEntity>::field_data_static<4 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Destroyed"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x07BCF325; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4 + StormReflTypeInfo<GameServerEntityBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerEntity::m_Destroyed; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerEntity *>(obj); return &ptr->m_Destroyed; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerEntity *>(obj); return &ptr->m_Destroyed; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerEntity>::field_data<4 + StormReflTypeInfo<GameServerEntityBase>::fields_n, Self> : public StormReflTypeInfo<ProjectileServerEntity>::field_data_static<4 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Destroyed; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Destroyed; }
  void SetDefault() { self.m_Destroyed = StormReflTypeInfo<ProjectileServerEntity>::GetDefault().m_Destroyed; }
};

template <>
struct StormReflTypeInfo<ProjectileServerEntity>::field_data_static<5 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  using member_type = int8_t; // signed char
  static constexpr auto GetName() { return "m_DamageBoost"; }
  static constexpr auto GetType() { return "signed char"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA632E9D9; }
  static constexpr unsigned GetTypeNameHash() { return 0xFA467DC9; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5 + StormReflTypeInfo<GameServerEntityBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerEntity::m_DamageBoost; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerEntity *>(obj); return &ptr->m_DamageBoost; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerEntity *>(obj); return &ptr->m_DamageBoost; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerEntity>::field_data<5 + StormReflTypeInfo<GameServerEntityBase>::fields_n, Self> : public StormReflTypeInfo<ProjectileServerEntity>::field_data_static<5 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int8_t> & Get() { return self.m_DamageBoost; }
  std::add_const_t<std::remove_reference_t<int8_t>> & Get() const { return self.m_DamageBoost; }
  void SetDefault() { self.m_DamageBoost = StormReflTypeInfo<ProjectileServerEntity>::GetDefault().m_DamageBoost; }
};

template <>
struct StormReflTypeInfo<ProjectileServerEntity>::field_data_static<6 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  using member_type = ServerEntityComponent<ProjectileMotionBase, ProjectileMotionBaseConfig>; // ServerEntityComponent<ProjectileMotionBase, ProjectileMotionBaseConfig>
  static constexpr auto GetName() { return "m_Motion"; }
  static constexpr auto GetType() { return "ServerEntityComponent<ProjectileMotionBase, ProjectileMotionBaseConfig>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB8C1F620; }
  static constexpr unsigned GetTypeNameHash() { return 0x286CB8FE; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6 + StormReflTypeInfo<GameServerEntityBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerEntity::m_Motion; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerEntity *>(obj); return &ptr->m_Motion; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerEntity *>(obj); return &ptr->m_Motion; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerEntity>::field_data<6 + StormReflTypeInfo<GameServerEntityBase>::fields_n, Self> : public StormReflTypeInfo<ProjectileServerEntity>::field_data_static<6 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ServerEntityComponent<ProjectileMotionBase, ProjectileMotionBaseConfig>> & Get() { return self.m_Motion; }
  std::add_const_t<std::remove_reference_t<ServerEntityComponent<ProjectileMotionBase, ProjectileMotionBaseConfig>>> & Get() const { return self.m_Motion; }
  void SetDefault() { self.m_Motion = StormReflTypeInfo<ProjectileServerEntity>::GetDefault().m_Motion; }
};

template <>
struct StormReflTypeInfo<ProjectileServerEntity>::field_data_static<7 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  using member_type = ServerEntityComponent<ProjectileResponseBase, ProjectileResponseBaseConfig>; // ServerEntityComponent<ProjectileResponseBase, ProjectileResponseBaseConfig>
  static constexpr auto GetName() { return "m_Response"; }
  static constexpr auto GetType() { return "ServerEntityComponent<ProjectileResponseBase, ProjectileResponseBaseConfig>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC857DFD5; }
  static constexpr unsigned GetTypeNameHash() { return 0xC73BC8CE; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7 + StormReflTypeInfo<GameServerEntityBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerEntity::m_Response; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerEntity *>(obj); return &ptr->m_Response; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerEntity *>(obj); return &ptr->m_Response; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerEntity>::field_data<7 + StormReflTypeInfo<GameServerEntityBase>::fields_n, Self> : public StormReflTypeInfo<ProjectileServerEntity>::field_data_static<7 + StormReflTypeInfo<GameServerEntityBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ServerEntityComponent<ProjectileResponseBase, ProjectileResponseBaseConfig>> & Get() { return self.m_Response; }
  std::add_const_t<std::remove_reference_t<ServerEntityComponent<ProjectileResponseBase, ProjectileResponseBaseConfig>>> & Get() const { return self.m_Response; }
  void SetDefault() { self.m_Response = StormReflTypeInfo<ProjectileServerEntity>::GetDefault().m_Response; }
};

template <>
struct StormReflFuncInfo<ProjectileServerEntity>
{
  using MyBase = GameServerEntityBase;
  static constexpr int funcs_n = 0 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};

namespace StormReflFileInfo
{
  struct ProjectileServerEntity
  {
    static const int types_n = 3;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct ProjectileServerEntity::type_info<0>
  {
    using type = ::ProjectileServerEntitySpawnData;
  };

  template <>
  struct ProjectileServerEntity::type_info<1>
  {
    using type = ::ProjectileServerEntityInitData;
  };

  template <>
  struct ProjectileServerEntity::type_info<2>
  {
    using type = ::ProjectileServerEntity;
  };

}

