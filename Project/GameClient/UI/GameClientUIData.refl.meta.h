#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameClientUIData.refl.h"


template <>
struct StormReflTypeInfo<NoiseAlert>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "NoiseAlert"; }
  static constexpr auto GetNameHash() { return 0xBA206007; }
  static constexpr bool HasDefault() { return true; }
  static NoiseAlert & GetDefault() { static NoiseAlert def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<NoiseAlert *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const NoiseAlert *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<NoiseAlert *>(ptr);
    if(typeid(NoiseAlert).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const NoiseAlert *>(ptr);
    if(typeid(NoiseAlert).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<NoiseAlert>::field_data_static<0>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "angle"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x00814509; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &NoiseAlert::angle; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<NoiseAlert *>(obj); return &ptr->angle; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const NoiseAlert *>(obj); return &ptr->angle; }
};

template <typename Self>
struct StormReflTypeInfo<NoiseAlert>::field_data<0, Self> : public StormReflTypeInfo<NoiseAlert>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.angle; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.angle; }
  void SetDefault() { self.angle = StormReflTypeInfo<NoiseAlert>::GetDefault().angle; }
};

template <>
struct StormReflTypeInfo<NoiseAlert>::field_data_static<1>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "alpha"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD0E0396A; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &NoiseAlert::alpha; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<NoiseAlert *>(obj); return &ptr->alpha; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const NoiseAlert *>(obj); return &ptr->alpha; }
};

template <typename Self>
struct StormReflTypeInfo<NoiseAlert>::field_data<1, Self> : public StormReflTypeInfo<NoiseAlert>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.alpha; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.alpha; }
  void SetDefault() { self.alpha = StormReflTypeInfo<NoiseAlert>::GetDefault().alpha; }
};

template <>
struct StormReflTypeInfo<GameClientUIData>
{
  using MyBase = void;
  static constexpr int fields_n = 13;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameClientUIData"; }
  static constexpr auto GetNameHash() { return 0x3254A1CC; }
  static constexpr bool HasDefault() { return true; }
  static GameClientUIData & GetDefault() { static GameClientUIData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameClientUIData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameClientUIData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameClientUIData *>(ptr);
    if(typeid(GameClientUIData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameClientUIData *>(ptr);
    if(typeid(GameClientUIData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameClientUIData>::field_data_static<0>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "timer_pre_round"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x574BCAFF; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameClientUIData::timer_pre_round; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameClientUIData *>(obj); return &ptr->timer_pre_round; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameClientUIData *>(obj); return &ptr->timer_pre_round; }
};

template <typename Self>
struct StormReflTypeInfo<GameClientUIData>::field_data<0, Self> : public StormReflTypeInfo<GameClientUIData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.timer_pre_round; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.timer_pre_round; }
  void SetDefault() { self.timer_pre_round = StormReflTypeInfo<GameClientUIData>::GetDefault().timer_pre_round; }
};

template <>
struct StormReflTypeInfo<GameClientUIData>::field_data_static<1>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "timer_post_round"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6913485C; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameClientUIData::timer_post_round; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameClientUIData *>(obj); return &ptr->timer_post_round; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameClientUIData *>(obj); return &ptr->timer_post_round; }
};

template <typename Self>
struct StormReflTypeInfo<GameClientUIData>::field_data<1, Self> : public StormReflTypeInfo<GameClientUIData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.timer_post_round; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.timer_post_round; }
  void SetDefault() { self.timer_post_round = StormReflTypeInfo<GameClientUIData>::GetDefault().timer_post_round; }
};

template <>
struct StormReflTypeInfo<GameClientUIData>::field_data_static<2>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "timer_scale"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x91E2DEB2; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameClientUIData::timer_scale; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameClientUIData *>(obj); return &ptr->timer_scale; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameClientUIData *>(obj); return &ptr->timer_scale; }
};

template <typename Self>
struct StormReflTypeInfo<GameClientUIData>::field_data<2, Self> : public StormReflTypeInfo<GameClientUIData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.timer_scale; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.timer_scale; }
  void SetDefault() { self.timer_scale = StormReflTypeInfo<GameClientUIData>::GetDefault().timer_scale; }
};

template <>
struct StormReflTypeInfo<GameClientUIData>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "timer"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6AD0DE1A; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameClientUIData::timer; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameClientUIData *>(obj); return &ptr->timer; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameClientUIData *>(obj); return &ptr->timer; }
};

template <typename Self>
struct StormReflTypeInfo<GameClientUIData>::field_data<3, Self> : public StormReflTypeInfo<GameClientUIData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.timer; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.timer; }
  void SetDefault() { self.timer = StormReflTypeInfo<GameClientUIData>::GetDefault().timer; }
};

template <>
struct StormReflTypeInfo<GameClientUIData>::field_data_static<4>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "tutorial_hint"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4B00841E; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameClientUIData::tutorial_hint; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameClientUIData *>(obj); return &ptr->tutorial_hint; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameClientUIData *>(obj); return &ptr->tutorial_hint; }
};

template <typename Self>
struct StormReflTypeInfo<GameClientUIData>::field_data<4, Self> : public StormReflTypeInfo<GameClientUIData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.tutorial_hint; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.tutorial_hint; }
  void SetDefault() { self.tutorial_hint = StormReflTypeInfo<GameClientUIData>::GetDefault().tutorial_hint; }
};

template <>
struct StormReflTypeInfo<GameClientUIData>::field_data_static<5>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "tutorial_hint_x"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1CB0998C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GameClientUIData::tutorial_hint_x; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameClientUIData *>(obj); return &ptr->tutorial_hint_x; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameClientUIData *>(obj); return &ptr->tutorial_hint_x; }
};

template <typename Self>
struct StormReflTypeInfo<GameClientUIData>::field_data<5, Self> : public StormReflTypeInfo<GameClientUIData>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.tutorial_hint_x; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.tutorial_hint_x; }
  void SetDefault() { self.tutorial_hint_x = StormReflTypeInfo<GameClientUIData>::GetDefault().tutorial_hint_x; }
};

template <>
struct StormReflTypeInfo<GameClientUIData>::field_data_static<6>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "tutorial_hint_y"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6BB7A91A; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &GameClientUIData::tutorial_hint_y; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameClientUIData *>(obj); return &ptr->tutorial_hint_y; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameClientUIData *>(obj); return &ptr->tutorial_hint_y; }
};

template <typename Self>
struct StormReflTypeInfo<GameClientUIData>::field_data<6, Self> : public StormReflTypeInfo<GameClientUIData>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.tutorial_hint_y; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.tutorial_hint_y; }
  void SetDefault() { self.tutorial_hint_y = StormReflTypeInfo<GameClientUIData>::GetDefault().tutorial_hint_y; }
};

template <>
struct StormReflTypeInfo<GameClientUIData>::field_data_static<7>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "health"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCEDA2313; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &GameClientUIData::health; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameClientUIData *>(obj); return &ptr->health; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameClientUIData *>(obj); return &ptr->health; }
};

template <typename Self>
struct StormReflTypeInfo<GameClientUIData>::field_data<7, Self> : public StormReflTypeInfo<GameClientUIData>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.health; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.health; }
  void SetDefault() { self.health = StormReflTypeInfo<GameClientUIData>::GetDefault().health; }
};

template <>
struct StormReflTypeInfo<GameClientUIData>::field_data_static<8>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "ammo"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEF8F7E2A; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &GameClientUIData::ammo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameClientUIData *>(obj); return &ptr->ammo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameClientUIData *>(obj); return &ptr->ammo; }
};

template <typename Self>
struct StormReflTypeInfo<GameClientUIData>::field_data<8, Self> : public StormReflTypeInfo<GameClientUIData>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.ammo; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.ammo; }
  void SetDefault() { self.ammo = StormReflTypeInfo<GameClientUIData>::GetDefault().ammo; }
};

template <>
struct StormReflTypeInfo<GameClientUIData>::field_data_static<9>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "max_ammo"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x90F45BD2; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &GameClientUIData::max_ammo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameClientUIData *>(obj); return &ptr->max_ammo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameClientUIData *>(obj); return &ptr->max_ammo; }
};

template <typename Self>
struct StormReflTypeInfo<GameClientUIData>::field_data<9, Self> : public StormReflTypeInfo<GameClientUIData>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.max_ammo; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.max_ammo; }
  void SetDefault() { self.max_ammo = StormReflTypeInfo<GameClientUIData>::GetDefault().max_ammo; }
};

template <>
struct StormReflTypeInfo<GameClientUIData>::field_data_static<10>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "lives"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5D347E5E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &GameClientUIData::lives; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameClientUIData *>(obj); return &ptr->lives; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameClientUIData *>(obj); return &ptr->lives; }
};

template <typename Self>
struct StormReflTypeInfo<GameClientUIData>::field_data<10, Self> : public StormReflTypeInfo<GameClientUIData>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.lives; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.lives; }
  void SetDefault() { self.lives = StormReflTypeInfo<GameClientUIData>::GetDefault().lives; }
};

template <>
struct StormReflTypeInfo<GameClientUIData>::field_data_static<11>
{
  using member_type = std::vector<NoiseAlert>; // std::vector<NoiseAlert, std::allocator<NoiseAlert> >
  static constexpr auto GetName() { return "alerts"; }
  static constexpr auto GetType() { return "std::vector<NoiseAlert, std::allocator<NoiseAlert> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF77AC06B; }
  static constexpr unsigned GetTypeNameHash() { return 0xECB77B2B; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &GameClientUIData::alerts; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameClientUIData *>(obj); return &ptr->alerts; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameClientUIData *>(obj); return &ptr->alerts; }
};

template <typename Self>
struct StormReflTypeInfo<GameClientUIData>::field_data<11, Self> : public StormReflTypeInfo<GameClientUIData>::field_data_static<11>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<NoiseAlert>> & Get() { return self.alerts; }
  std::add_const_t<std::remove_reference_t<std::vector<NoiseAlert>>> & Get() const { return self.alerts; }
  void SetDefault() { self.alerts = StormReflTypeInfo<GameClientUIData>::GetDefault().alerts; }
};

template <>
struct StormReflTypeInfo<GameClientUIData>::field_data_static<12>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "num_alerts"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4E5B97D3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 12; }
  static constexpr auto GetMemberPtr() { return &GameClientUIData::num_alerts; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameClientUIData *>(obj); return &ptr->num_alerts; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameClientUIData *>(obj); return &ptr->num_alerts; }
};

template <typename Self>
struct StormReflTypeInfo<GameClientUIData>::field_data<12, Self> : public StormReflTypeInfo<GameClientUIData>::field_data_static<12>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.num_alerts; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.num_alerts; }
  void SetDefault() { self.num_alerts = StormReflTypeInfo<GameClientUIData>::GetDefault().num_alerts; }
};

template <>
struct StormReflTypeInfo<UpgradeInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 6;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UpgradeInfo"; }
  static constexpr auto GetNameHash() { return 0xE7D98CC7; }
  static constexpr bool HasDefault() { return true; }
  static UpgradeInfo & GetDefault() { static UpgradeInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UpgradeInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UpgradeInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UpgradeInfo *>(ptr);
    if(typeid(UpgradeInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UpgradeInfo *>(ptr);
    if(typeid(UpgradeInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UpgradeInfo>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "damage"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x11C8546C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UpgradeInfo::damage; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UpgradeInfo *>(obj); return &ptr->damage; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UpgradeInfo *>(obj); return &ptr->damage; }
};

template <typename Self>
struct StormReflTypeInfo<UpgradeInfo>::field_data<0, Self> : public StormReflTypeInfo<UpgradeInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.damage; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.damage; }
  void SetDefault() { self.damage = StormReflTypeInfo<UpgradeInfo>::GetDefault().damage; }
};

template <>
struct StormReflTypeInfo<UpgradeInfo>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "ammo"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEF8F7E2A; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UpgradeInfo::ammo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UpgradeInfo *>(obj); return &ptr->ammo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UpgradeInfo *>(obj); return &ptr->ammo; }
};

template <typename Self>
struct StormReflTypeInfo<UpgradeInfo>::field_data<1, Self> : public StormReflTypeInfo<UpgradeInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.ammo; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.ammo; }
  void SetDefault() { self.ammo = StormReflTypeInfo<UpgradeInfo>::GetDefault().ammo; }
};

template <>
struct StormReflTypeInfo<UpgradeInfo>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "health"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCEDA2313; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UpgradeInfo::health; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UpgradeInfo *>(obj); return &ptr->health; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UpgradeInfo *>(obj); return &ptr->health; }
};

template <typename Self>
struct StormReflTypeInfo<UpgradeInfo>::field_data<2, Self> : public StormReflTypeInfo<UpgradeInfo>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.health; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.health; }
  void SetDefault() { self.health = StormReflTypeInfo<UpgradeInfo>::GetDefault().health; }
};

template <>
struct StormReflTypeInfo<UpgradeInfo>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "speed"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0F26FEF6; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UpgradeInfo::speed; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UpgradeInfo *>(obj); return &ptr->speed; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UpgradeInfo *>(obj); return &ptr->speed; }
};

template <typename Self>
struct StormReflTypeInfo<UpgradeInfo>::field_data<3, Self> : public StormReflTypeInfo<UpgradeInfo>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.speed; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.speed; }
  void SetDefault() { self.speed = StormReflTypeInfo<UpgradeInfo>::GetDefault().speed; }
};

template <>
struct StormReflTypeInfo<UpgradeInfo>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "life"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x19CD3EFE; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UpgradeInfo::life; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UpgradeInfo *>(obj); return &ptr->life; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UpgradeInfo *>(obj); return &ptr->life; }
};

template <typename Self>
struct StormReflTypeInfo<UpgradeInfo>::field_data<4, Self> : public StormReflTypeInfo<UpgradeInfo>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.life; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.life; }
  void SetDefault() { self.life = StormReflTypeInfo<UpgradeInfo>::GetDefault().life; }
};

template <>
struct StormReflTypeInfo<UpgradeInfo>::field_data_static<5>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "rate"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDFEC3F39; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UpgradeInfo::rate; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UpgradeInfo *>(obj); return &ptr->rate; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UpgradeInfo *>(obj); return &ptr->rate; }
};

template <typename Self>
struct StormReflTypeInfo<UpgradeInfo>::field_data<5, Self> : public StormReflTypeInfo<UpgradeInfo>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.rate; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.rate; }
  void SetDefault() { self.rate = StormReflTypeInfo<UpgradeInfo>::GetDefault().rate; }
};

namespace StormReflFileInfo
{
  struct GameClientUIData
  {
    static const int types_n = 3;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameClientUIData::type_info<0>
  {
    using type = ::NoiseAlert;
  };

  template <>
  struct GameClientUIData::type_info<1>
  {
    using type = ::GameClientUIData;
  };

  template <>
  struct GameClientUIData::type_info<2>
  {
    using type = ::UpgradeInfo;
  };

}

