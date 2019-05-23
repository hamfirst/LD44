#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "ProjectileResponseDefault.refl.h"
#include "Game/ServerEntities/Projectile/Response/ProjectileResponseBase.refl.meta.h"
#include "Game/GameplayEvents/DamageType.refl.meta.h"


template <>
struct StormReflTypeInfo<ProjectileResponseDefaultConfig>
{
  using MyBase = ProjectileResponseBaseConfig;
  static constexpr int fields_n = 2 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ProjectileResponseDefaultConfig"; }
  static constexpr auto GetNameHash() { return 0xA7048A1E; }
  static constexpr bool HasDefault() { return true; }
  static ProjectileResponseDefaultConfig & GetDefault() { static ProjectileResponseDefaultConfig def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ProjectileResponseDefaultConfig *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x6E067AD3 == type_name_hash) return static_cast<ProjectileResponseBaseConfig *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileResponseDefaultConfig *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x6E067AD3 == type_name_hash) return static_cast<const ProjectileResponseBaseConfig *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ProjectileResponseDefaultConfig *>(ptr);
    if(typeid(ProjectileResponseDefaultConfig).hash_code() == type_id_hash) return c;
    if(typeid(ProjectileResponseBaseConfig).hash_code() == type_id_hash) return static_cast<ProjectileResponseBaseConfig *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileResponseDefaultConfig *>(ptr);
    if(typeid(ProjectileResponseDefaultConfig).hash_code() == type_id_hash) return c;
    if(typeid(ProjectileResponseBaseConfig).hash_code() == type_id_hash) return static_cast<const ProjectileResponseBaseConfig *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ProjectileResponseDefaultConfig>::field_data_static<0 + StormReflTypeInfo<ProjectileResponseBaseConfig>::fields_n>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Damage"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5CF703A4; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<ProjectileResponseBaseConfig>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ProjectileResponseDefaultConfig::m_Damage; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileResponseDefaultConfig *>(obj); return &ptr->m_Damage; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileResponseDefaultConfig *>(obj); return &ptr->m_Damage; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileResponseDefaultConfig>::field_data<0 + StormReflTypeInfo<ProjectileResponseBaseConfig>::fields_n, Self> : public StormReflTypeInfo<ProjectileResponseDefaultConfig>::field_data_static<0 + StormReflTypeInfo<ProjectileResponseBaseConfig>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Damage; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Damage; }
  void SetDefault() { self.m_Damage = StormReflTypeInfo<ProjectileResponseDefaultConfig>::GetDefault().m_Damage; }
};

template <>
struct StormReflTypeInfo<ProjectileResponseDefaultConfig>::field_data_static<1 + StormReflTypeInfo<ProjectileResponseBaseConfig>::fields_n>
{
  using member_type = REnum<DamageType>; // REnum<DamageType>
  static constexpr auto GetName() { return "m_Type"; }
  static constexpr auto GetType() { return "REnum<DamageType>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB243C236; }
  static constexpr unsigned GetTypeNameHash() { return 0x33D1B477; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<ProjectileResponseBaseConfig>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ProjectileResponseDefaultConfig::m_Type; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileResponseDefaultConfig *>(obj); return &ptr->m_Type; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileResponseDefaultConfig *>(obj); return &ptr->m_Type; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileResponseDefaultConfig>::field_data<1 + StormReflTypeInfo<ProjectileResponseBaseConfig>::fields_n, Self> : public StormReflTypeInfo<ProjectileResponseDefaultConfig>::field_data_static<1 + StormReflTypeInfo<ProjectileResponseBaseConfig>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, REnum<DamageType>> & Get() { return self.m_Type; }
  std::add_const_t<std::remove_reference_t<REnum<DamageType>>> & Get() const { return self.m_Type; }
  void SetDefault() { self.m_Type = StormReflTypeInfo<ProjectileResponseDefaultConfig>::GetDefault().m_Type; }
};

template <>
struct StormReflTypeInfo<ProjectileResponseDefault>
{
  using MyBase = ProjectileResponseBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ProjectileResponseDefault"; }
  static constexpr auto GetNameHash() { return 0x74D310AB; }
  static constexpr bool HasDefault() { return true; }
  static ProjectileResponseDefault & GetDefault() { static ProjectileResponseDefault def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ProjectileResponseDefault *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xB8C052D5 == type_name_hash) return static_cast<ProjectileResponseBase *>(c);
    if(0xF703938B == type_name_hash) return static_cast<ServerEntityComponentBase<ProjectileResponseBaseConfig> *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileResponseDefault *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xB8C052D5 == type_name_hash) return static_cast<const ProjectileResponseBase *>(c);
    if(0xF703938B == type_name_hash) return static_cast<const ServerEntityComponentBase<ProjectileResponseBaseConfig> *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ProjectileResponseDefault *>(ptr);
    if(typeid(ProjectileResponseDefault).hash_code() == type_id_hash) return c;
    if(typeid(ProjectileResponseBase).hash_code() == type_id_hash) return static_cast<ProjectileResponseBase *>(c);
    if(typeid(ServerEntityComponentBase<ProjectileResponseBaseConfig>).hash_code() == type_id_hash) return static_cast<ServerEntityComponentBase<ProjectileResponseBaseConfig> *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileResponseDefault *>(ptr);
    if(typeid(ProjectileResponseDefault).hash_code() == type_id_hash) return c;
    if(typeid(ProjectileResponseBase).hash_code() == type_id_hash) return static_cast<const ProjectileResponseBase *>(c);
    if(typeid(ServerEntityComponentBase<ProjectileResponseBaseConfig>).hash_code() == type_id_hash) return static_cast<const ServerEntityComponentBase<ProjectileResponseBaseConfig> *>(c);
    return nullptr;
  }

};

namespace StormReflFileInfo
{
  struct ProjectileResponseDefault
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct ProjectileResponseDefault::type_info<0>
  {
    using type = ::ProjectileResponseDefaultConfig;
  };

  template <>
  struct ProjectileResponseDefault::type_info<1>
  {
    using type = ::ProjectileResponseDefault;
  };

}

