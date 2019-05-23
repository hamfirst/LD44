#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "ClientEntityDef.refl.h"
#include "Runtime/ClientComponent/ClientComponentInitData.refl.meta.h"


template <>
struct StormReflTypeInfo<ClientEntityDef>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ClientEntityDef"; }
  static constexpr auto GetNameHash() { return 0xD9FFD674; }
  static constexpr bool HasDefault() { return true; }
  static ClientEntityDef & GetDefault() { static ClientEntityDef def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ClientEntityDef *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ClientEntityDef *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ClientEntityDef *>(ptr);
    if(typeid(ClientEntityDef).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ClientEntityDef *>(ptr);
    if(typeid(ClientEntityDef).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ClientEntityDef>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Sprite"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7822D856; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ClientEntityDef::m_Sprite; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ClientEntityDef *>(obj); return &ptr->m_Sprite; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ClientEntityDef *>(obj); return &ptr->m_Sprite; }
};

template <typename Self>
struct StormReflTypeInfo<ClientEntityDef>::field_data<0, Self> : public StormReflTypeInfo<ClientEntityDef>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Sprite; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Sprite; }
  void SetDefault() { self.m_Sprite = StormReflTypeInfo<ClientEntityDef>::GetDefault().m_Sprite; }
};

template <>
struct StormReflTypeInfo<ClientEntityDef>::annotations<0>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<ClientEntityDef>::annotations<0>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "file: sprite"; }
  static constexpr uint32_t GetAnnotationHash() { return 0x1563DF3B; }
};

template <>
struct StormReflTypeInfo<ClientEntityDef>::field_data_static<1>
{
  using member_type = RMergeList<RPolymorphic<ClientComponentInitData> >; // RMergeList<RPolymorphicBase<ClientComponentInitData, TypeDatabase<ClientComponentInitData, void>, TypeDatabaseTypeInfo<ClientComponentInitData, void>, false> >
  static constexpr auto GetName() { return "m_Components"; }
  static constexpr auto GetType() { return "RMergeList<RPolymorphicBase<ClientComponentInitData, TypeDatabase<ClientComponentInitData, void>, TypeDatabaseTypeInfo<ClientComponentInitData, void>, false> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x64F11C30; }
  static constexpr unsigned GetTypeNameHash() { return 0x62FD550F; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ClientEntityDef::m_Components; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ClientEntityDef *>(obj); return &ptr->m_Components; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ClientEntityDef *>(obj); return &ptr->m_Components; }
};

template <typename Self>
struct StormReflTypeInfo<ClientEntityDef>::field_data<1, Self> : public StormReflTypeInfo<ClientEntityDef>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RPolymorphic<ClientComponentInitData> >> & Get() { return self.m_Components; }
  std::add_const_t<std::remove_reference_t<RMergeList<RPolymorphic<ClientComponentInitData> >>> & Get() const { return self.m_Components; }
  void SetDefault() { self.m_Components = StormReflTypeInfo<ClientEntityDef>::GetDefault().m_Components; }
};

namespace StormReflFileInfo
{
  struct ClientEntityDef
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct ClientEntityDef::type_info<0>
  {
    using type = ::ClientEntityDef;
  };

}

