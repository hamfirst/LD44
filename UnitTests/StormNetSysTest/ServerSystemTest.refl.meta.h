#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "ServerSystemTest.refl.h"


template <>
struct StormReflTypeInfo<ServerSystemTestState>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerSystemTestState"; }
  static constexpr auto GetNameHash() { return 0x35B17696; }
  static constexpr bool HasDefault() { return true; }
  static ServerSystemTestState & GetDefault() { static ServerSystemTestState def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ServerSystemTestState *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ServerSystemTestState *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ServerSystemTestState *>(ptr);
    if(typeid(ServerSystemTestState).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ServerSystemTestState *>(ptr);
    if(typeid(ServerSystemTestState).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ServerSystemTestState>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Frame"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x38CEACAD; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ServerSystemTestState::m_Frame; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerSystemTestState *>(obj); return &ptr->m_Frame; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerSystemTestState *>(obj); return &ptr->m_Frame; }
};

template <typename Self>
struct StormReflTypeInfo<ServerSystemTestState>::field_data<0, Self> : public StormReflTypeInfo<ServerSystemTestState>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Frame; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Frame; }
  void SetDefault() { self.m_Frame = StormReflTypeInfo<ServerSystemTestState>::GetDefault().m_Frame; }
};

template <>
struct StormReflTypeInfo<ServerSystemTestState>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Inputs"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4E5EF786; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ServerSystemTestState::m_Inputs; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerSystemTestState *>(obj); return &ptr->m_Inputs; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerSystemTestState *>(obj); return &ptr->m_Inputs; }
};

template <typename Self>
struct StormReflTypeInfo<ServerSystemTestState>::field_data<1, Self> : public StormReflTypeInfo<ServerSystemTestState>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Inputs; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Inputs; }
  void SetDefault() { self.m_Inputs = StormReflTypeInfo<ServerSystemTestState>::GetDefault().m_Inputs; }
};

template <>
struct StormReflTypeInfo<ServerSystemTestState>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ExternalEvents"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF6206F58; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &ServerSystemTestState::m_ExternalEvents; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerSystemTestState *>(obj); return &ptr->m_ExternalEvents; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerSystemTestState *>(obj); return &ptr->m_ExternalEvents; }
};

template <typename Self>
struct StormReflTypeInfo<ServerSystemTestState>::field_data<2, Self> : public StormReflTypeInfo<ServerSystemTestState>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ExternalEvents; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ExternalEvents; }
  void SetDefault() { self.m_ExternalEvents = StormReflTypeInfo<ServerSystemTestState>::GetDefault().m_ExternalEvents; }
};

template <>
struct StormReflTypeInfo<ServerSystemTestClientData>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerSystemTestClientData"; }
  static constexpr auto GetNameHash() { return 0xD87754BF; }
  static constexpr bool HasDefault() { return true; }
  static ServerSystemTestClientData & GetDefault() { static ServerSystemTestClientData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ServerSystemTestClientData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ServerSystemTestClientData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ServerSystemTestClientData *>(ptr);
    if(typeid(ServerSystemTestClientData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ServerSystemTestClientData *>(ptr);
    if(typeid(ServerSystemTestClientData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ServerSystemTestClientData>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ServerSystemTestClientData::m_Data; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerSystemTestClientData *>(obj); return &ptr->m_Data; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerSystemTestClientData *>(obj); return &ptr->m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<ServerSystemTestClientData>::field_data<0, Self> : public StormReflTypeInfo<ServerSystemTestClientData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<ServerSystemTestClientData>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<ServerSystemTestInput>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerSystemTestInput"; }
  static constexpr auto GetNameHash() { return 0x4E0A96BA; }
  static constexpr bool HasDefault() { return true; }
  static ServerSystemTestInput & GetDefault() { static ServerSystemTestInput def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ServerSystemTestInput *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ServerSystemTestInput *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ServerSystemTestInput *>(ptr);
    if(typeid(ServerSystemTestInput).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ServerSystemTestInput *>(ptr);
    if(typeid(ServerSystemTestInput).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ServerSystemTestInput>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ServerSystemTestInput::m_Data; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerSystemTestInput *>(obj); return &ptr->m_Data; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerSystemTestInput *>(obj); return &ptr->m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<ServerSystemTestInput>::field_data<0, Self> : public StormReflTypeInfo<ServerSystemTestInput>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<ServerSystemTestInput>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<ServerSystemTestEffectEvent>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerSystemTestEffectEvent"; }
  static constexpr auto GetNameHash() { return 0xF547E464; }
  static constexpr bool HasDefault() { return true; }
  static ServerSystemTestEffectEvent & GetDefault() { static ServerSystemTestEffectEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ServerSystemTestEffectEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ServerSystemTestEffectEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ServerSystemTestEffectEvent *>(ptr);
    if(typeid(ServerSystemTestEffectEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ServerSystemTestEffectEvent *>(ptr);
    if(typeid(ServerSystemTestEffectEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ServerSystemTestEffectEvent>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_PositionX"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA6033D27; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ServerSystemTestEffectEvent::m_PositionX; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerSystemTestEffectEvent *>(obj); return &ptr->m_PositionX; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerSystemTestEffectEvent *>(obj); return &ptr->m_PositionX; }
};

template <typename Self>
struct StormReflTypeInfo<ServerSystemTestEffectEvent>::field_data<0, Self> : public StormReflTypeInfo<ServerSystemTestEffectEvent>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_PositionX; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_PositionX; }
  void SetDefault() { self.m_PositionX = StormReflTypeInfo<ServerSystemTestEffectEvent>::GetDefault().m_PositionX; }
};

template <>
struct StormReflTypeInfo<ServerSystemTestEffectEvent>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_PositionY"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD1040DB1; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ServerSystemTestEffectEvent::m_PositionY; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerSystemTestEffectEvent *>(obj); return &ptr->m_PositionY; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerSystemTestEffectEvent *>(obj); return &ptr->m_PositionY; }
};

template <typename Self>
struct StormReflTypeInfo<ServerSystemTestEffectEvent>::field_data<1, Self> : public StormReflTypeInfo<ServerSystemTestEffectEvent>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_PositionY; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_PositionY; }
  void SetDefault() { self.m_PositionY = StormReflTypeInfo<ServerSystemTestEffectEvent>::GetDefault().m_PositionY; }
};

template <>
struct StormReflTypeInfo<ServerSystemTestEffectEvent>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &ServerSystemTestEffectEvent::m_Data; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerSystemTestEffectEvent *>(obj); return &ptr->m_Data; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerSystemTestEffectEvent *>(obj); return &ptr->m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<ServerSystemTestEffectEvent>::field_data<2, Self> : public StormReflTypeInfo<ServerSystemTestEffectEvent>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<ServerSystemTestEffectEvent>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<ServerSystemTestAuthorityEvent>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerSystemTestAuthorityEvent"; }
  static constexpr auto GetNameHash() { return 0x83853226; }
  static constexpr bool HasDefault() { return true; }
  static ServerSystemTestAuthorityEvent & GetDefault() { static ServerSystemTestAuthorityEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ServerSystemTestAuthorityEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ServerSystemTestAuthorityEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ServerSystemTestAuthorityEvent *>(ptr);
    if(typeid(ServerSystemTestAuthorityEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ServerSystemTestAuthorityEvent *>(ptr);
    if(typeid(ServerSystemTestAuthorityEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ServerSystemTestAuthorityEvent>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ServerSystemTestAuthorityEvent::m_Data; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerSystemTestAuthorityEvent *>(obj); return &ptr->m_Data; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerSystemTestAuthorityEvent *>(obj); return &ptr->m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<ServerSystemTestAuthorityEvent>::field_data<0, Self> : public StormReflTypeInfo<ServerSystemTestAuthorityEvent>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<ServerSystemTestAuthorityEvent>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<ServerSystemTestClientLocalData>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerSystemTestClientLocalData"; }
  static constexpr auto GetNameHash() { return 0x74E9CA88; }
  static constexpr bool HasDefault() { return true; }
  static ServerSystemTestClientLocalData & GetDefault() { static ServerSystemTestClientLocalData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ServerSystemTestClientLocalData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ServerSystemTestClientLocalData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ServerSystemTestClientLocalData *>(ptr);
    if(typeid(ServerSystemTestClientLocalData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ServerSystemTestClientLocalData *>(ptr);
    if(typeid(ServerSystemTestClientLocalData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ServerSystemTestClientLocalData>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ServerSystemTestClientLocalData::m_Data; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerSystemTestClientLocalData *>(obj); return &ptr->m_Data; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerSystemTestClientLocalData *>(obj); return &ptr->m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<ServerSystemTestClientLocalData>::field_data<0, Self> : public StormReflTypeInfo<ServerSystemTestClientLocalData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<ServerSystemTestClientLocalData>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<ServerSystemTestClientLocalEvent>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerSystemTestClientLocalEvent"; }
  static constexpr auto GetNameHash() { return 0x0CAF2B6E; }
  static constexpr bool HasDefault() { return true; }
  static ServerSystemTestClientLocalEvent & GetDefault() { static ServerSystemTestClientLocalEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ServerSystemTestClientLocalEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ServerSystemTestClientLocalEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ServerSystemTestClientLocalEvent *>(ptr);
    if(typeid(ServerSystemTestClientLocalEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ServerSystemTestClientLocalEvent *>(ptr);
    if(typeid(ServerSystemTestClientLocalEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ServerSystemTestClientLocalEvent>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ServerSystemTestClientLocalEvent::m_Data; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerSystemTestClientLocalEvent *>(obj); return &ptr->m_Data; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerSystemTestClientLocalEvent *>(obj); return &ptr->m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<ServerSystemTestClientLocalEvent>::field_data<0, Self> : public StormReflTypeInfo<ServerSystemTestClientLocalEvent>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<ServerSystemTestClientLocalEvent>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<ServerSystemTestExternalEvent>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerSystemTestExternalEvent"; }
  static constexpr auto GetNameHash() { return 0xDE7D010E; }
  static constexpr bool HasDefault() { return true; }
  static ServerSystemTestExternalEvent & GetDefault() { static ServerSystemTestExternalEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ServerSystemTestExternalEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ServerSystemTestExternalEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ServerSystemTestExternalEvent *>(ptr);
    if(typeid(ServerSystemTestExternalEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ServerSystemTestExternalEvent *>(ptr);
    if(typeid(ServerSystemTestExternalEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ServerSystemTestExternalEvent>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ServerSystemTestExternalEvent::m_Data; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ServerSystemTestExternalEvent *>(obj); return &ptr->m_Data; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ServerSystemTestExternalEvent *>(obj); return &ptr->m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<ServerSystemTestExternalEvent>::field_data<0, Self> : public StormReflTypeInfo<ServerSystemTestExternalEvent>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<ServerSystemTestExternalEvent>::GetDefault().m_Data; }
};

namespace StormReflFileInfo
{
  struct ServerSystemTest
  {
    static const int types_n = 8;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct ServerSystemTest::type_info<0>
  {
    using type = ::ServerSystemTestState;
  };

  template <>
  struct ServerSystemTest::type_info<1>
  {
    using type = ::ServerSystemTestClientData;
  };

  template <>
  struct ServerSystemTest::type_info<2>
  {
    using type = ::ServerSystemTestInput;
  };

  template <>
  struct ServerSystemTest::type_info<3>
  {
    using type = ::ServerSystemTestEffectEvent;
  };

  template <>
  struct ServerSystemTest::type_info<4>
  {
    using type = ::ServerSystemTestAuthorityEvent;
  };

  template <>
  struct ServerSystemTest::type_info<5>
  {
    using type = ::ServerSystemTestClientLocalData;
  };

  template <>
  struct ServerSystemTest::type_info<6>
  {
    using type = ::ServerSystemTestClientLocalEvent;
  };

  template <>
  struct ServerSystemTest::type_info<7>
  {
    using type = ::ServerSystemTestExternalEvent;
  };

}

