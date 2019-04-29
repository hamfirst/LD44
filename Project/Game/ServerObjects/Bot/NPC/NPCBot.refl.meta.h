#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "NPCBot.refl.h"
#include "Game/ServerObjects/Bot/BotServerObject.refl.meta.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.meta.h"
#include "Runtime/Map/MapHandles.refl.meta.h"


template <>
struct StormReflTypeInfo<NPCBotInitData>
{
  using MyBase = BotServerObjectInitData;
  static constexpr int fields_n = 1 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "NPCBotInitData"; }
  static constexpr auto GetNameHash() { return 0xF41E916F; }
  static constexpr bool HasDefault() { return true; }
  static NPCBotInitData & GetDefault() { static NPCBotInitData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<NPCBotInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x1C601FCD == type_name_hash) return static_cast<BotServerObjectInitData *>(c);
    if(0xE8EFD458 == type_name_hash) return static_cast<GameServerObjectBaseInitData *>(c);
    if(0x2D36BDE7 == type_name_hash) return static_cast<ServerObjectInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const NPCBotInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x1C601FCD == type_name_hash) return static_cast<const BotServerObjectInitData *>(c);
    if(0xE8EFD458 == type_name_hash) return static_cast<const GameServerObjectBaseInitData *>(c);
    if(0x2D36BDE7 == type_name_hash) return static_cast<const ServerObjectInitData *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<NPCBotInitData *>(ptr);
    if(typeid(NPCBotInitData).hash_code() == type_id_hash) return c;
    if(typeid(BotServerObjectInitData).hash_code() == type_id_hash) return static_cast<BotServerObjectInitData *>(c);
    if(typeid(GameServerObjectBaseInitData).hash_code() == type_id_hash) return static_cast<GameServerObjectBaseInitData *>(c);
    if(typeid(ServerObjectInitData).hash_code() == type_id_hash) return static_cast<ServerObjectInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const NPCBotInitData *>(ptr);
    if(typeid(NPCBotInitData).hash_code() == type_id_hash) return c;
    if(typeid(BotServerObjectInitData).hash_code() == type_id_hash) return static_cast<const BotServerObjectInitData *>(c);
    if(typeid(GameServerObjectBaseInitData).hash_code() == type_id_hash) return static_cast<const GameServerObjectBaseInitData *>(c);
    if(typeid(ServerObjectInitData).hash_code() == type_id_hash) return static_cast<const ServerObjectInitData *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<NPCBotInitData>::field_data_static<0 + StormReflTypeInfo<BotServerObjectInitData>::fields_n>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_NPCIndex"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7BE697A3; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<BotServerObjectInitData>::fields_n; }
  static constexpr auto GetMemberPtr() { return &NPCBotInitData::m_NPCIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<NPCBotInitData *>(obj); return &ptr->m_NPCIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const NPCBotInitData *>(obj); return &ptr->m_NPCIndex; }
};

template <typename Self>
struct StormReflTypeInfo<NPCBotInitData>::field_data<0 + StormReflTypeInfo<BotServerObjectInitData>::fields_n, Self> : public StormReflTypeInfo<NPCBotInitData>::field_data_static<0 + StormReflTypeInfo<BotServerObjectInitData>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_NPCIndex; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_NPCIndex; }
  void SetDefault() { self.m_NPCIndex = StormReflTypeInfo<NPCBotInitData>::GetDefault().m_NPCIndex; }
};

template <>
struct StormReflTypeInfo<NPCBot>
{
  using MyBase = BotServerObject;
  static constexpr int fields_n = 2 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "NPCBot"; }
  static constexpr auto GetNameHash() { return 0xF3316944; }
  static constexpr bool HasDefault() { return true; }
  static NPCBot & GetDefault() { static NPCBot def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<NPCBot *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xF3F6D91E == type_name_hash) return static_cast<BotServerObject *>(c);
    if(0x25DA07B6 == type_name_hash) return static_cast<GameServerObjectBase *>(c);
    if(0x9D89FBB7 == type_name_hash) return static_cast<ServerObject *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const NPCBot *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xF3F6D91E == type_name_hash) return static_cast<const BotServerObject *>(c);
    if(0x25DA07B6 == type_name_hash) return static_cast<const GameServerObjectBase *>(c);
    if(0x9D89FBB7 == type_name_hash) return static_cast<const ServerObject *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<NPCBot *>(ptr);
    if(typeid(NPCBot).hash_code() == type_id_hash) return c;
    if(typeid(BotServerObject).hash_code() == type_id_hash) return static_cast<BotServerObject *>(c);
    if(typeid(GameServerObjectBase).hash_code() == type_id_hash) return static_cast<GameServerObjectBase *>(c);
    if(typeid(ServerObject).hash_code() == type_id_hash) return static_cast<ServerObject *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const NPCBot *>(ptr);
    if(typeid(NPCBot).hash_code() == type_id_hash) return c;
    if(typeid(BotServerObject).hash_code() == type_id_hash) return static_cast<const BotServerObject *>(c);
    if(typeid(GameServerObjectBase).hash_code() == type_id_hash) return static_cast<const GameServerObjectBase *>(c);
    if(typeid(ServerObject).hash_code() == type_id_hash) return static_cast<const ServerObject *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<NPCBot>::field_data_static<0 + StormReflTypeInfo<BotServerObject>::fields_n>
{
  using member_type = BotBehaviorTree; // StormBehaviorTree<BotServerObject, GameLogicContainer>
  static constexpr auto GetName() { return "m_Tree"; }
  static constexpr auto GetType() { return "StormBehaviorTree<BotServerObject, GameLogicContainer>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x89A3CBC3; }
  static constexpr unsigned GetTypeNameHash() { return 0xD4BF05A2; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<BotServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &NPCBot::m_Tree; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<NPCBot *>(obj); return &ptr->m_Tree; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const NPCBot *>(obj); return &ptr->m_Tree; }
};

template <typename Self>
struct StormReflTypeInfo<NPCBot>::field_data<0 + StormReflTypeInfo<BotServerObject>::fields_n, Self> : public StormReflTypeInfo<NPCBot>::field_data_static<0 + StormReflTypeInfo<BotServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, BotBehaviorTree> & Get() { return self.m_Tree; }
  std::add_const_t<std::remove_reference_t<BotBehaviorTree>> & Get() const { return self.m_Tree; }
  void SetDefault() { self.m_Tree = StormReflTypeInfo<NPCBot>::GetDefault().m_Tree; }
};

template <>
struct StormReflTypeInfo<NPCBot>::field_data_static<1 + StormReflTypeInfo<BotServerObject>::fields_n>
{
  using member_type = int8_t; // signed char
  static constexpr auto GetName() { return "m_NPCIndex"; }
  static constexpr auto GetType() { return "signed char"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7BE697A3; }
  static constexpr unsigned GetTypeNameHash() { return 0xFA467DC9; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<BotServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &NPCBot::m_NPCIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<NPCBot *>(obj); return &ptr->m_NPCIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const NPCBot *>(obj); return &ptr->m_NPCIndex; }
};

template <typename Self>
struct StormReflTypeInfo<NPCBot>::field_data<1 + StormReflTypeInfo<BotServerObject>::fields_n, Self> : public StormReflTypeInfo<NPCBot>::field_data_static<1 + StormReflTypeInfo<BotServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int8_t> & Get() { return self.m_NPCIndex; }
  std::add_const_t<std::remove_reference_t<int8_t>> & Get() const { return self.m_NPCIndex; }
  void SetDefault() { self.m_NPCIndex = StormReflTypeInfo<NPCBot>::GetDefault().m_NPCIndex; }
};

template <>
struct StormReflFuncInfo<NPCBot>
{
  using MyBase = BotServerObject;
  static constexpr int funcs_n = 1 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};

template <>
struct StormReflFuncInfo<NPCBot>::func_data_static<0 + StormReflFuncInfo<BotServerObject>::funcs_n>
{
  using func_ptr_type = bool (NPCBot::*)(const DamageEvent &, const EventMetaData &);
  using return_type = bool;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleDamageEvent"; }
  static constexpr auto GetReturnType() { return "bool"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x38A81F11; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFunctionIndex() { return 0 + StormReflFuncInfo<BotServerObject>::funcs_n; }
  static constexpr func_ptr_type GetFunctionPtr() { return &NPCBot::HandleDamageEvent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<NPCBot>::func_data_static<0 + StormReflFuncInfo<BotServerObject>::funcs_n>::param_info<0>
{
  using param_type = const DamageEvent &;
  static constexpr auto GetName() { return "ev"; }
  static constexpr auto GetType() { return "const DamageEvent &"; }
  static constexpr unsigned GetNameHash() { return 0xE0355914; }
  static constexpr unsigned GetTypeNameHash() { return 0x18F056E3; }
};

template <>
struct StormReflFuncInfo<NPCBot>::func_data_static<0 + StormReflFuncInfo<BotServerObject>::funcs_n>::param_info<1>
{
  using param_type = const EventMetaData &;
  static constexpr auto GetName() { return "meta"; }
  static constexpr auto GetType() { return "const EventMetaData &"; }
  static constexpr unsigned GetNameHash() { return 0xD7F21435; }
  static constexpr unsigned GetTypeNameHash() { return 0x039083D7; }
};

namespace StormReflFileInfo
{
  struct NPCBot
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct NPCBot::type_info<0>
  {
    using type = ::NPCBotInitData;
  };

  template <>
  struct NPCBot::type_info<1>
  {
    using type = ::NPCBot;
  };

}

