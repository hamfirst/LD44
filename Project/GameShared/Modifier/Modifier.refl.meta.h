#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "Modifier.refl.h"


template <>
struct StormReflEnumInfo<ModifierType>
{
  static constexpr int elems_n = 5;
  static constexpr auto GetName() { return "ModifierType"; }
  static constexpr auto GetNameHash() { return 0xE0D02B3D; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<ModifierType>::elems<0>
{
  static constexpr auto GetName() { return "kAdd"; }
  static constexpr auto GetNameHash() { return 0xF775430B; }
  static constexpr auto GetValue() { return ModifierType::kAdd; }
};

template <>
struct StormReflEnumInfo<ModifierType>::elems<1>
{
  static constexpr auto GetName() { return "kSubtract"; }
  static constexpr auto GetNameHash() { return 0x8533AC61; }
  static constexpr auto GetValue() { return ModifierType::kSubtract; }
};

template <>
struct StormReflEnumInfo<ModifierType>::elems<2>
{
  static constexpr auto GetName() { return "kMultiply"; }
  static constexpr auto GetNameHash() { return 0xB5DD97A3; }
  static constexpr auto GetValue() { return ModifierType::kMultiply; }
};

template <>
struct StormReflEnumInfo<ModifierType>::elems<3>
{
  static constexpr auto GetName() { return "kDivide"; }
  static constexpr auto GetNameHash() { return 0x212DAEBC; }
  static constexpr auto GetValue() { return ModifierType::kDivide; }
};

template <>
struct StormReflEnumInfo<ModifierType>::elems<4>
{
  static constexpr auto GetName() { return "kSet"; }
  static constexpr auto GetNameHash() { return 0xEC7B1530; }
  static constexpr auto GetValue() { return ModifierType::kSet; }
};

template <>
struct StormReflTypeInfo<ModifierConfigElement>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ModifierConfigElement"; }
  static constexpr auto GetNameHash() { return 0x2475CF3A; }
  static constexpr bool HasDefault() { return true; }
  static ModifierConfigElement & GetDefault() { static ModifierConfigElement def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ModifierConfigElement *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ModifierConfigElement *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ModifierConfigElement *>(ptr);
    if(typeid(ModifierConfigElement).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ModifierConfigElement *>(ptr);
    if(typeid(ModifierConfigElement).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ModifierConfigElement>::field_data_static<0>
{
  using member_type = REnum<ModifierType>; // REnum<ModifierType>
  static constexpr auto GetName() { return "m_Type"; }
  static constexpr auto GetType() { return "REnum<ModifierType>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB243C236; }
  static constexpr unsigned GetTypeNameHash() { return 0x42F30244; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ModifierConfigElement::m_Type; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ModifierConfigElement *>(obj); return &ptr->m_Type; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ModifierConfigElement *>(obj); return &ptr->m_Type; }
};

template <typename Self>
struct StormReflTypeInfo<ModifierConfigElement>::field_data<0, Self> : public StormReflTypeInfo<ModifierConfigElement>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, REnum<ModifierType>> & Get() { return self.m_Type; }
  std::add_const_t<std::remove_reference_t<REnum<ModifierType>>> & Get() const { return self.m_Type; }
  void SetDefault() { self.m_Type = StormReflTypeInfo<ModifierConfigElement>::GetDefault().m_Type; }
};

template <>
struct StormReflTypeInfo<ModifierConfigElement>::field_data_static<1>
{
  using member_type = RDeterministicFloat<GameNetVal>; // RDeterministicFloat<NetFixedPoint<long, 32, 16> >
  static constexpr auto GetName() { return "m_Value"; }
  static constexpr auto GetType() { return "RDeterministicFloat<NetFixedPoint<long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9041C854; }
  static constexpr unsigned GetTypeNameHash() { return 0x9C9647A3; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ModifierConfigElement::m_Value; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ModifierConfigElement *>(obj); return &ptr->m_Value; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ModifierConfigElement *>(obj); return &ptr->m_Value; }
};

template <typename Self>
struct StormReflTypeInfo<ModifierConfigElement>::field_data<1, Self> : public StormReflTypeInfo<ModifierConfigElement>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RDeterministicFloat<GameNetVal>> & Get() { return self.m_Value; }
  std::add_const_t<std::remove_reference_t<RDeterministicFloat<GameNetVal>>> & Get() const { return self.m_Value; }
  void SetDefault() { self.m_Value = StormReflTypeInfo<ModifierConfigElement>::GetDefault().m_Value; }
};

namespace StormReflFileInfo
{
  struct Modifier
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct Modifier::type_info<0>
  {
    using type = ::ModifierConfigElement;
  };

}

