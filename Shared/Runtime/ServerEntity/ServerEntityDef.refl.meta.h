#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "ServerEntityDef.refl.h"
#include "Runtime/ServerEntity/ServerEntityInitData.refl.meta.h"


template <>
struct StormReflTypeInfo<ServerEntityDef>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerEntityDef"; }
  static constexpr auto GetNameHash() { return 0x35BC670D; }
  static constexpr bool HasDefault() { return true; }
  static ServerEntityDef & GetDefault() { static ServerEntityDef def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ServerEntityDef *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ServerEntityDef *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ServerEntityDef *>(ptr);
    if(typeid(ServerEntityDef).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ServerEntityDef *>(ptr);
    if(typeid(ServerEntityDef).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ServerEntityDef>::field_data_static<0>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_IsStatic"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB784F6D1; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ServerEntityDef::m_IsStatic; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerEntityDef *>(obj); return &ptr->m_IsStatic; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerEntityDef *>(obj); return &ptr->m_IsStatic; }
};

template <typename Self>
struct StormReflTypeInfo<ServerEntityDef>::field_data<0, Self> : public StormReflTypeInfo<ServerEntityDef>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_IsStatic; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_IsStatic; }
  void SetDefault() { self.m_IsStatic = StormReflTypeInfo<ServerEntityDef>::GetDefault().m_IsStatic; }
};

template <>
struct StormReflTypeInfo<ServerEntityDef>::field_data_static<1>
{
  using member_type = RPolymorphic<ServerEntityInitData>; // RPolymorphicBase<ServerEntityInitData, TypeDatabase<ServerEntityInitData, void>, TypeDatabaseTypeInfo<ServerEntityInitData, void>, false>
  static constexpr auto GetName() { return "m_InitData"; }
  static constexpr auto GetType() { return "RPolymorphicBase<ServerEntityInitData, TypeDatabase<ServerEntityInitData, void>, TypeDatabaseTypeInfo<ServerEntityInitData, void>, false>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x880F1CB3; }
  static constexpr unsigned GetTypeNameHash() { return 0xF7518000; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ServerEntityDef::m_InitData; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerEntityDef *>(obj); return &ptr->m_InitData; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerEntityDef *>(obj); return &ptr->m_InitData; }
};

template <typename Self>
struct StormReflTypeInfo<ServerEntityDef>::field_data<1, Self> : public StormReflTypeInfo<ServerEntityDef>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RPolymorphic<ServerEntityInitData>> & Get() { return self.m_InitData; }
  std::add_const_t<std::remove_reference_t<RPolymorphic<ServerEntityInitData>>> & Get() const { return self.m_InitData; }
  void SetDefault() { self.m_InitData = StormReflTypeInfo<ServerEntityDef>::GetDefault().m_InitData; }
};

namespace StormReflFileInfo
{
  struct ServerEntityDef
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct ServerEntityDef::type_info<0>
  {
    using type = ::ServerEntityDef;
  };

}

