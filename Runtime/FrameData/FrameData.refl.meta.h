#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "FrameData.refl.h"
#include "Foundation/BasicTypes/BasicTypes.refl.meta.h"


template <>
struct StormReflEnumInfo<FrameDataDefType>
{
  static constexpr int elems_n = 3;
  static constexpr auto GetName() { return "FrameDataDefType"; }
  static constexpr auto GetNameHash() { return 0xCD6F2DAB; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<FrameDataDefType>::elems<0>
{
  static constexpr auto GetName() { return "kSingleBox"; }
  static constexpr auto GetNameHash() { return 0x1F11133D; }
  static constexpr auto GetValue() { return FrameDataDefType::kSingleBox; }
};

template <>
struct StormReflEnumInfo<FrameDataDefType>::elems<1>
{
  static constexpr auto GetName() { return "kMultiBox"; }
  static constexpr auto GetNameHash() { return 0xCE18C508; }
  static constexpr auto GetValue() { return FrameDataDefType::kMultiBox; }
};

template <>
struct StormReflEnumInfo<FrameDataDefType>::elems<2>
{
  static constexpr auto GetName() { return "kSingleLine"; }
  static constexpr auto GetNameHash() { return 0x4F67990E; }
  static constexpr auto GetValue() { return FrameDataDefType::kSingleLine; }
};

template <>
struct StormReflTypeInfo<FrameDataSingleBox>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "FrameDataSingleBox"; }
  static constexpr auto GetNameHash() { return 0x29848608; }
  static FrameDataSingleBox & GetDefault() { static FrameDataSingleBox def; return def; }
};

template <>
struct StormReflTypeInfo<FrameDataSingleBox>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_FrameDataName"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x05708CE5; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &FrameDataSingleBox::m_FrameDataName; }
};

template <typename Self>
struct StormReflTypeInfo<FrameDataSingleBox>::field_data<0, Self> : public StormReflTypeInfo<FrameDataSingleBox>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_FrameDataName; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_FrameDataName; }
  void SetDefault() { self.m_FrameDataName = StormReflTypeInfo<FrameDataSingleBox>::GetDefault().m_FrameDataName; }
};

template <>
struct StormReflTypeInfo<FrameDataSingleBox>::field_data_static<1>
{
  using member_type = ROpaque<Box>; // ROpaque<Box>
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "ROpaque<Box>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0xE527A8B8; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &FrameDataSingleBox::m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<FrameDataSingleBox>::field_data<1, Self> : public StormReflTypeInfo<FrameDataSingleBox>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ROpaque<Box>> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<ROpaque<Box>>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<FrameDataSingleBox>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<FrameDataMultiBox>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "FrameDataMultiBox"; }
  static constexpr auto GetNameHash() { return 0x58C706A2; }
  static FrameDataMultiBox & GetDefault() { static FrameDataMultiBox def; return def; }
};

template <>
struct StormReflTypeInfo<FrameDataMultiBox>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_FrameDataName"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x05708CE5; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &FrameDataMultiBox::m_FrameDataName; }
};

template <typename Self>
struct StormReflTypeInfo<FrameDataMultiBox>::field_data<0, Self> : public StormReflTypeInfo<FrameDataMultiBox>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_FrameDataName; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_FrameDataName; }
  void SetDefault() { self.m_FrameDataName = StormReflTypeInfo<FrameDataMultiBox>::GetDefault().m_FrameDataName; }
};

template <>
struct StormReflTypeInfo<FrameDataMultiBox>::field_data_static<1>
{
  using member_type = ROpaque<std::vector<Box> >; // ROpaque<std::vector<Box, std::allocator<Box> > >
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "ROpaque<std::vector<Box, std::allocator<Box> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0x69BF77B3; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &FrameDataMultiBox::m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<FrameDataMultiBox>::field_data<1, Self> : public StormReflTypeInfo<FrameDataMultiBox>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ROpaque<std::vector<Box> >> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<ROpaque<std::vector<Box> >>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<FrameDataMultiBox>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<FrameDataSingleLineInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "FrameDataSingleLineInfo"; }
  static constexpr auto GetNameHash() { return 0x24E2064A; }
  static FrameDataSingleLineInfo & GetDefault() { static FrameDataSingleLineInfo def; return def; }
};

template <>
struct StormReflTypeInfo<FrameDataSingleLineInfo>::field_data_static<0>
{
  using member_type = Vector2; // Vector2
  static constexpr auto GetName() { return "m_Start"; }
  static constexpr auto GetType() { return "Vector2"; }
  static constexpr unsigned GetFieldNameHash() { return 0x124FC5EF; }
  static constexpr unsigned GetTypeNameHash() { return 0x29CA61A5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &FrameDataSingleLineInfo::m_Start; }
};

template <typename Self>
struct StormReflTypeInfo<FrameDataSingleLineInfo>::field_data<0, Self> : public StormReflTypeInfo<FrameDataSingleLineInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, Vector2> & Get() { return self.m_Start; }
  std::add_const_t<std::remove_reference_t<Vector2>> & Get() const { return self.m_Start; }
  void SetDefault() { self.m_Start = StormReflTypeInfo<FrameDataSingleLineInfo>::GetDefault().m_Start; }
};

template <>
struct StormReflTypeInfo<FrameDataSingleLineInfo>::field_data_static<1>
{
  using member_type = Vector2; // Vector2
  static constexpr auto GetName() { return "m_End"; }
  static constexpr auto GetType() { return "Vector2"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF31EF756; }
  static constexpr unsigned GetTypeNameHash() { return 0x29CA61A5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &FrameDataSingleLineInfo::m_End; }
};

template <typename Self>
struct StormReflTypeInfo<FrameDataSingleLineInfo>::field_data<1, Self> : public StormReflTypeInfo<FrameDataSingleLineInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, Vector2> & Get() { return self.m_End; }
  std::add_const_t<std::remove_reference_t<Vector2>> & Get() const { return self.m_End; }
  void SetDefault() { self.m_End = StormReflTypeInfo<FrameDataSingleLineInfo>::GetDefault().m_End; }
};

template <>
struct StormReflTypeInfo<FrameDataSingleLine>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "FrameDataSingleLine"; }
  static constexpr auto GetNameHash() { return 0x19E2C8B8; }
  static FrameDataSingleLine & GetDefault() { static FrameDataSingleLine def; return def; }
};

template <>
struct StormReflTypeInfo<FrameDataSingleLine>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_FrameDataName"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x05708CE5; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &FrameDataSingleLine::m_FrameDataName; }
};

template <typename Self>
struct StormReflTypeInfo<FrameDataSingleLine>::field_data<0, Self> : public StormReflTypeInfo<FrameDataSingleLine>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_FrameDataName; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_FrameDataName; }
  void SetDefault() { self.m_FrameDataName = StormReflTypeInfo<FrameDataSingleLine>::GetDefault().m_FrameDataName; }
};

template <>
struct StormReflTypeInfo<FrameDataSingleLine>::field_data_static<1>
{
  using member_type = ROpaque<FrameDataSingleLineInfo>; // ROpaque<FrameDataSingleLineInfo>
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "ROpaque<FrameDataSingleLineInfo>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0xC29FEB17; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &FrameDataSingleLine::m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<FrameDataSingleLine>::field_data<1, Self> : public StormReflTypeInfo<FrameDataSingleLine>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ROpaque<FrameDataSingleLineInfo>> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<ROpaque<FrameDataSingleLineInfo>>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<FrameDataSingleLine>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<FrameData>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "FrameData"; }
  static constexpr auto GetNameHash() { return 0x4108D867; }
  static FrameData & GetDefault() { static FrameData def; return def; }
};

template <>
struct StormReflTypeInfo<FrameData>::field_data_static<0>
{
  using member_type = RMergeList<FrameDataSingleBox>; // RMergeList<FrameDataSingleBox>
  static constexpr auto GetName() { return "m_SingleBoxData"; }
  static constexpr auto GetType() { return "RMergeList<FrameDataSingleBox>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC513C98D; }
  static constexpr unsigned GetTypeNameHash() { return 0xFC5C61A6; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &FrameData::m_SingleBoxData; }
};

template <typename Self>
struct StormReflTypeInfo<FrameData>::field_data<0, Self> : public StormReflTypeInfo<FrameData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<FrameDataSingleBox>> & Get() { return self.m_SingleBoxData; }
  std::add_const_t<std::remove_reference_t<RMergeList<FrameDataSingleBox>>> & Get() const { return self.m_SingleBoxData; }
  void SetDefault() { self.m_SingleBoxData = StormReflTypeInfo<FrameData>::GetDefault().m_SingleBoxData; }
};

template <>
struct StormReflTypeInfo<FrameData>::field_data_static<1>
{
  using member_type = RMergeList<FrameDataMultiBox>; // RMergeList<FrameDataMultiBox>
  static constexpr auto GetName() { return "m_MultiBoxData"; }
  static constexpr auto GetType() { return "RMergeList<FrameDataMultiBox>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x83FE1079; }
  static constexpr unsigned GetTypeNameHash() { return 0xE8E4DBAF; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &FrameData::m_MultiBoxData; }
};

template <typename Self>
struct StormReflTypeInfo<FrameData>::field_data<1, Self> : public StormReflTypeInfo<FrameData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<FrameDataMultiBox>> & Get() { return self.m_MultiBoxData; }
  std::add_const_t<std::remove_reference_t<RMergeList<FrameDataMultiBox>>> & Get() const { return self.m_MultiBoxData; }
  void SetDefault() { self.m_MultiBoxData = StormReflTypeInfo<FrameData>::GetDefault().m_MultiBoxData; }
};

template <>
struct StormReflTypeInfo<FrameData>::field_data_static<2>
{
  using member_type = RMergeList<FrameDataSingleLine>; // RMergeList<FrameDataSingleLine>
  static constexpr auto GetName() { return "m_SingleLineData"; }
  static constexpr auto GetType() { return "RMergeList<FrameDataSingleLine>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9EBB4AAE; }
  static constexpr unsigned GetTypeNameHash() { return 0xF795127A; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &FrameData::m_SingleLineData; }
};

template <typename Self>
struct StormReflTypeInfo<FrameData>::field_data<2, Self> : public StormReflTypeInfo<FrameData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<FrameDataSingleLine>> & Get() { return self.m_SingleLineData; }
  std::add_const_t<std::remove_reference_t<RMergeList<FrameDataSingleLine>>> & Get() const { return self.m_SingleLineData; }
  void SetDefault() { self.m_SingleLineData = StormReflTypeInfo<FrameData>::GetDefault().m_SingleLineData; }
};

template <>
struct StormReflTypeInfo<FrameDataDefElem>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "FrameDataDefElem"; }
  static constexpr auto GetNameHash() { return 0x064912EC; }
  static FrameDataDefElem & GetDefault() { static FrameDataDefElem def; return def; }
};

template <>
struct StormReflTypeInfo<FrameDataDefElem>::field_data_static<0>
{
  using member_type = FrameDataDefType; // FrameDataDefType
  static constexpr auto GetName() { return "m_Type"; }
  static constexpr auto GetType() { return "FrameDataDefType"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB243C236; }
  static constexpr unsigned GetTypeNameHash() { return 0xCD6F2DAB; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &FrameDataDefElem::m_Type; }
};

template <typename Self>
struct StormReflTypeInfo<FrameDataDefElem>::field_data<0, Self> : public StormReflTypeInfo<FrameDataDefElem>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, FrameDataDefType> & Get() { return self.m_Type; }
  std::add_const_t<std::remove_reference_t<FrameDataDefType>> & Get() const { return self.m_Type; }
  void SetDefault() { self.m_Type = StormReflTypeInfo<FrameDataDefElem>::GetDefault().m_Type; }
};

template <>
struct StormReflTypeInfo<FrameDataDefElem>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &FrameDataDefElem::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<FrameDataDefElem>::field_data<1, Self> : public StormReflTypeInfo<FrameDataDefElem>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<FrameDataDefElem>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<FrameDataDef>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "FrameDataDef"; }
  static constexpr auto GetNameHash() { return 0x3E2BBD40; }
  static FrameDataDef & GetDefault() { static FrameDataDef def; return def; }
};

template <>
struct StormReflTypeInfo<FrameDataDef>::field_data_static<0>
{
  using member_type = std::vector<FrameDataDefElem>; // std::vector<FrameDataDefElem, std::allocator<FrameDataDefElem> >
  static constexpr auto GetName() { return "m_SpriteGlobalData"; }
  static constexpr auto GetType() { return "std::vector<FrameDataDefElem, std::allocator<FrameDataDefElem> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFCB7C27F; }
  static constexpr unsigned GetTypeNameHash() { return 0xBB7F3FE0; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &FrameDataDef::m_SpriteGlobalData; }
};

template <typename Self>
struct StormReflTypeInfo<FrameDataDef>::field_data<0, Self> : public StormReflTypeInfo<FrameDataDef>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<FrameDataDefElem>> & Get() { return self.m_SpriteGlobalData; }
  std::add_const_t<std::remove_reference_t<std::vector<FrameDataDefElem>>> & Get() const { return self.m_SpriteGlobalData; }
  void SetDefault() { self.m_SpriteGlobalData = StormReflTypeInfo<FrameDataDef>::GetDefault().m_SpriteGlobalData; }
};

template <>
struct StormReflTypeInfo<FrameDataDef>::field_data_static<1>
{
  using member_type = std::vector<FrameDataDefElem>; // std::vector<FrameDataDefElem, std::allocator<FrameDataDefElem> >
  static constexpr auto GetName() { return "m_SpriteFrameData"; }
  static constexpr auto GetType() { return "std::vector<FrameDataDefElem, std::allocator<FrameDataDefElem> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2AEB2A2B; }
  static constexpr unsigned GetTypeNameHash() { return 0xBB7F3FE0; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &FrameDataDef::m_SpriteFrameData; }
};

template <typename Self>
struct StormReflTypeInfo<FrameDataDef>::field_data<1, Self> : public StormReflTypeInfo<FrameDataDef>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<FrameDataDefElem>> & Get() { return self.m_SpriteFrameData; }
  std::add_const_t<std::remove_reference_t<std::vector<FrameDataDefElem>>> & Get() const { return self.m_SpriteFrameData; }
  void SetDefault() { self.m_SpriteFrameData = StormReflTypeInfo<FrameDataDef>::GetDefault().m_SpriteFrameData; }
};

template <>
struct StormReflTypeInfo<FrameDataDef>::field_data_static<2>
{
  using member_type = std::vector<FrameDataDefElem>; // std::vector<FrameDataDefElem, std::allocator<FrameDataDefElem> >
  static constexpr auto GetName() { return "m_TileGlobalData"; }
  static constexpr auto GetType() { return "std::vector<FrameDataDefElem, std::allocator<FrameDataDefElem> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDD8768A7; }
  static constexpr unsigned GetTypeNameHash() { return 0xBB7F3FE0; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &FrameDataDef::m_TileGlobalData; }
};

template <typename Self>
struct StormReflTypeInfo<FrameDataDef>::field_data<2, Self> : public StormReflTypeInfo<FrameDataDef>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<FrameDataDefElem>> & Get() { return self.m_TileGlobalData; }
  std::add_const_t<std::remove_reference_t<std::vector<FrameDataDefElem>>> & Get() const { return self.m_TileGlobalData; }
  void SetDefault() { self.m_TileGlobalData = StormReflTypeInfo<FrameDataDef>::GetDefault().m_TileGlobalData; }
};

template <>
struct StormReflTypeInfo<FrameDataDef>::field_data_static<3>
{
  using member_type = std::vector<FrameDataDefElem>; // std::vector<FrameDataDefElem, std::allocator<FrameDataDefElem> >
  static constexpr auto GetName() { return "m_TileFrameData"; }
  static constexpr auto GetType() { return "std::vector<FrameDataDefElem, std::allocator<FrameDataDefElem> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAEB5471F; }
  static constexpr unsigned GetTypeNameHash() { return 0xBB7F3FE0; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &FrameDataDef::m_TileFrameData; }
};

template <typename Self>
struct StormReflTypeInfo<FrameDataDef>::field_data<3, Self> : public StormReflTypeInfo<FrameDataDef>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<FrameDataDefElem>> & Get() { return self.m_TileFrameData; }
  std::add_const_t<std::remove_reference_t<std::vector<FrameDataDefElem>>> & Get() const { return self.m_TileFrameData; }
  void SetDefault() { self.m_TileFrameData = StormReflTypeInfo<FrameDataDef>::GetDefault().m_TileFrameData; }
};

namespace StormReflFileInfo
{
  struct FrameData
  {
    static const int types_n = 7;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct FrameData::type_info<0>
  {
    using type = ::FrameDataSingleBox;
  };

  template <>
  struct FrameData::type_info<1>
  {
    using type = ::FrameDataMultiBox;
  };

  template <>
  struct FrameData::type_info<2>
  {
    using type = ::FrameDataSingleLineInfo;
  };

  template <>
  struct FrameData::type_info<3>
  {
    using type = ::FrameDataSingleLine;
  };

  template <>
  struct FrameData::type_info<4>
  {
    using type = ::FrameData;
  };

  template <>
  struct FrameData::type_info<5>
  {
    using type = ::FrameDataDefElem;
  };

  template <>
  struct FrameData::type_info<6>
  {
    using type = ::FrameDataDef;
  };

}
