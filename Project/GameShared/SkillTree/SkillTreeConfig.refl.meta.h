#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "SkillTreeConfig.refl.h"
#include "GameShared/Modifier/Modifier.refl.meta.h"


template <>
struct StormReflTypeInfo<SkillTreeRankElement>
{
  using MyBase = ModifierConfigElement;
  static constexpr int fields_n = 1 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "SkillTreeRankElement"; }
  static constexpr auto GetNameHash() { return 0x6BE0BC8E; }
  static constexpr bool HasDefault() { return true; }
  static SkillTreeRankElement & GetDefault() { static SkillTreeRankElement def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SkillTreeRankElement *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x2475CF3A == type_name_hash) return static_cast<ModifierConfigElement *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SkillTreeRankElement *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x2475CF3A == type_name_hash) return static_cast<const ModifierConfigElement *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SkillTreeRankElement *>(ptr);
    if(typeid(SkillTreeRankElement).hash_code() == type_id_hash) return c;
    if(typeid(ModifierConfigElement).hash_code() == type_id_hash) return static_cast<ModifierConfigElement *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SkillTreeRankElement *>(ptr);
    if(typeid(SkillTreeRankElement).hash_code() == type_id_hash) return c;
    if(typeid(ModifierConfigElement).hash_code() == type_id_hash) return static_cast<const ModifierConfigElement *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<SkillTreeRankElement>::field_data_static<0 + StormReflTypeInfo<ModifierConfigElement>::fields_n>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Cost"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x26BB01E3; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<ModifierConfigElement>::fields_n; }
  static constexpr auto GetMemberPtr() { return &SkillTreeRankElement::m_Cost; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SkillTreeRankElement *>(obj); return &ptr->m_Cost; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SkillTreeRankElement *>(obj); return &ptr->m_Cost; }
};

template <typename Self>
struct StormReflTypeInfo<SkillTreeRankElement>::field_data<0 + StormReflTypeInfo<ModifierConfigElement>::fields_n, Self> : public StormReflTypeInfo<SkillTreeRankElement>::field_data_static<0 + StormReflTypeInfo<ModifierConfigElement>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Cost; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Cost; }
  void SetDefault() { self.m_Cost = StormReflTypeInfo<SkillTreeRankElement>::GetDefault().m_Cost; }
};

template <>
struct StormReflTypeInfo<SkillTreeConfigElement>
{
  using MyBase = void;
  static constexpr int fields_n = 9;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SkillTreeConfigElement"; }
  static constexpr auto GetNameHash() { return 0xCD5906F1; }
  static constexpr bool HasDefault() { return true; }
  static SkillTreeConfigElement & GetDefault() { static SkillTreeConfigElement def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SkillTreeConfigElement *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SkillTreeConfigElement *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SkillTreeConfigElement *>(ptr);
    if(typeid(SkillTreeConfigElement).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SkillTreeConfigElement *>(ptr);
    if(typeid(SkillTreeConfigElement).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<SkillTreeConfigElement>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_InternalName"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF79B5C65; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SkillTreeConfigElement::m_InternalName; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SkillTreeConfigElement *>(obj); return &ptr->m_InternalName; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SkillTreeConfigElement *>(obj); return &ptr->m_InternalName; }
};

template <typename Self>
struct StormReflTypeInfo<SkillTreeConfigElement>::field_data<0, Self> : public StormReflTypeInfo<SkillTreeConfigElement>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_InternalName; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_InternalName; }
  void SetDefault() { self.m_InternalName = StormReflTypeInfo<SkillTreeConfigElement>::GetDefault().m_InternalName; }
};

template <>
struct StormReflTypeInfo<SkillTreeConfigElement>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Category"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF060CDEF; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SkillTreeConfigElement::m_Category; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SkillTreeConfigElement *>(obj); return &ptr->m_Category; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SkillTreeConfigElement *>(obj); return &ptr->m_Category; }
};

template <typename Self>
struct StormReflTypeInfo<SkillTreeConfigElement>::field_data<1, Self> : public StormReflTypeInfo<SkillTreeConfigElement>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Category; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Category; }
  void SetDefault() { self.m_Category = StormReflTypeInfo<SkillTreeConfigElement>::GetDefault().m_Category; }
};

template <>
struct StormReflTypeInfo<SkillTreeConfigElement>::field_data_static<2>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_DisplayName"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8270647C; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SkillTreeConfigElement::m_DisplayName; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SkillTreeConfigElement *>(obj); return &ptr->m_DisplayName; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SkillTreeConfigElement *>(obj); return &ptr->m_DisplayName; }
};

template <typename Self>
struct StormReflTypeInfo<SkillTreeConfigElement>::field_data<2, Self> : public StormReflTypeInfo<SkillTreeConfigElement>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_DisplayName; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_DisplayName; }
  void SetDefault() { self.m_DisplayName = StormReflTypeInfo<SkillTreeConfigElement>::GetDefault().m_DisplayName; }
};

template <>
struct StormReflTypeInfo<SkillTreeConfigElement>::field_data_static<3>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Description"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x88BB47C2; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &SkillTreeConfigElement::m_Description; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SkillTreeConfigElement *>(obj); return &ptr->m_Description; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SkillTreeConfigElement *>(obj); return &ptr->m_Description; }
};

template <typename Self>
struct StormReflTypeInfo<SkillTreeConfigElement>::field_data<3, Self> : public StormReflTypeInfo<SkillTreeConfigElement>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Description; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Description; }
  void SetDefault() { self.m_Description = StormReflTypeInfo<SkillTreeConfigElement>::GetDefault().m_Description; }
};

template <>
struct StormReflTypeInfo<SkillTreeConfigElement>::field_data_static<4>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Icon"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5B09BCC4; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &SkillTreeConfigElement::m_Icon; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SkillTreeConfigElement *>(obj); return &ptr->m_Icon; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SkillTreeConfigElement *>(obj); return &ptr->m_Icon; }
};

template <typename Self>
struct StormReflTypeInfo<SkillTreeConfigElement>::field_data<4, Self> : public StormReflTypeInfo<SkillTreeConfigElement>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Icon; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Icon; }
  void SetDefault() { self.m_Icon = StormReflTypeInfo<SkillTreeConfigElement>::GetDefault().m_Icon; }
};

template <>
struct StormReflTypeInfo<SkillTreeConfigElement>::field_data_static<5>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_ValueName"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3CAF6335; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &SkillTreeConfigElement::m_ValueName; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SkillTreeConfigElement *>(obj); return &ptr->m_ValueName; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SkillTreeConfigElement *>(obj); return &ptr->m_ValueName; }
};

template <typename Self>
struct StormReflTypeInfo<SkillTreeConfigElement>::field_data<5, Self> : public StormReflTypeInfo<SkillTreeConfigElement>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_ValueName; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_ValueName; }
  void SetDefault() { self.m_ValueName = StormReflTypeInfo<SkillTreeConfigElement>::GetDefault().m_ValueName; }
};

template <>
struct StormReflTypeInfo<SkillTreeConfigElement>::field_data_static<6>
{
  using member_type = RMergeList<SkillTreeRankElement>; // RMergeList<SkillTreeRankElement>
  static constexpr auto GetName() { return "m_Ranks"; }
  static constexpr auto GetType() { return "RMergeList<SkillTreeRankElement>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x46D03074; }
  static constexpr unsigned GetTypeNameHash() { return 0xC2922052; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &SkillTreeConfigElement::m_Ranks; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SkillTreeConfigElement *>(obj); return &ptr->m_Ranks; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SkillTreeConfigElement *>(obj); return &ptr->m_Ranks; }
};

template <typename Self>
struct StormReflTypeInfo<SkillTreeConfigElement>::field_data<6, Self> : public StormReflTypeInfo<SkillTreeConfigElement>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<SkillTreeRankElement>> & Get() { return self.m_Ranks; }
  std::add_const_t<std::remove_reference_t<RMergeList<SkillTreeRankElement>>> & Get() const { return self.m_Ranks; }
  void SetDefault() { self.m_Ranks = StormReflTypeInfo<SkillTreeConfigElement>::GetDefault().m_Ranks; }
};

template <>
struct StormReflTypeInfo<SkillTreeConfigElement>::field_data_static<7>
{
  using member_type = RMergeList<RString>; // RMergeList<RString>
  static constexpr auto GetName() { return "m_Prerequisites"; }
  static constexpr auto GetType() { return "RMergeList<RString>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x973FA523; }
  static constexpr unsigned GetTypeNameHash() { return 0x8C9238EC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &SkillTreeConfigElement::m_Prerequisites; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SkillTreeConfigElement *>(obj); return &ptr->m_Prerequisites; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SkillTreeConfigElement *>(obj); return &ptr->m_Prerequisites; }
};

template <typename Self>
struct StormReflTypeInfo<SkillTreeConfigElement>::field_data<7, Self> : public StormReflTypeInfo<SkillTreeConfigElement>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RString>> & Get() { return self.m_Prerequisites; }
  std::add_const_t<std::remove_reference_t<RMergeList<RString>>> & Get() const { return self.m_Prerequisites; }
  void SetDefault() { self.m_Prerequisites = StormReflTypeInfo<SkillTreeConfigElement>::GetDefault().m_Prerequisites; }
};

template <>
struct StormReflTypeInfo<SkillTreeConfigElement>::field_data_static<8>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_PointsInCategoryRequired"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x72E77DB7; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &SkillTreeConfigElement::m_PointsInCategoryRequired; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SkillTreeConfigElement *>(obj); return &ptr->m_PointsInCategoryRequired; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SkillTreeConfigElement *>(obj); return &ptr->m_PointsInCategoryRequired; }
};

template <typename Self>
struct StormReflTypeInfo<SkillTreeConfigElement>::field_data<8, Self> : public StormReflTypeInfo<SkillTreeConfigElement>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_PointsInCategoryRequired; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_PointsInCategoryRequired; }
  void SetDefault() { self.m_PointsInCategoryRequired = StormReflTypeInfo<SkillTreeConfigElement>::GetDefault().m_PointsInCategoryRequired; }
};

template <>
struct StormReflTypeInfo<SkillTreeConfig>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SkillTreeConfig"; }
  static constexpr auto GetNameHash() { return 0x38E947BD; }
  static constexpr bool HasDefault() { return true; }
  static SkillTreeConfig & GetDefault() { static SkillTreeConfig def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SkillTreeConfig *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SkillTreeConfig *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SkillTreeConfig *>(ptr);
    if(typeid(SkillTreeConfig).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SkillTreeConfig *>(ptr);
    if(typeid(SkillTreeConfig).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<SkillTreeConfig>::field_data_static<0>
{
  using member_type = RMergeList<SkillTreeConfigElement>; // RMergeList<SkillTreeConfigElement>
  static constexpr auto GetName() { return "m_Elements"; }
  static constexpr auto GetType() { return "RMergeList<SkillTreeConfigElement>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB266D373; }
  static constexpr unsigned GetTypeNameHash() { return 0xF94B827C; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SkillTreeConfig::m_Elements; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SkillTreeConfig *>(obj); return &ptr->m_Elements; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SkillTreeConfig *>(obj); return &ptr->m_Elements; }
};

template <typename Self>
struct StormReflTypeInfo<SkillTreeConfig>::field_data<0, Self> : public StormReflTypeInfo<SkillTreeConfig>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<SkillTreeConfigElement>> & Get() { return self.m_Elements; }
  std::add_const_t<std::remove_reference_t<RMergeList<SkillTreeConfigElement>>> & Get() const { return self.m_Elements; }
  void SetDefault() { self.m_Elements = StormReflTypeInfo<SkillTreeConfig>::GetDefault().m_Elements; }
};

namespace StormReflFileInfo
{
  struct SkillTreeConfig
  {
    static const int types_n = 3;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct SkillTreeConfig::type_info<0>
  {
    using type = ::SkillTreeRankElement;
  };

  template <>
  struct SkillTreeConfig::type_info<1>
  {
    using type = ::SkillTreeConfigElement;
  };

  template <>
  struct SkillTreeConfig::type_info<2>
  {
    using type = ::SkillTreeConfig;
  };

}

