#pragma once
#include "StormRefl/StormReflMetaFuncs.h"
#include "StormData/StormDataTypeDatabaseRegister.h"

#include "Foundation/Update/UpdateRegistrationTemplates.h"
#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"
#include "Foundation/CallList/CallList.h"

#include "Runtime/ServerEntity/ServerEntityTypeInfo.h"
#include "Runtime/ServerEntity/ServerEntityInitDataTypeDatabase.h"
#include "Runtime/ServerEntity/ServerEntityComponent.h"

template <typename ParentType, typename FieldInfo, typename FieldType>
struct ServerEntityRegisterComponent
{
  static void Process(std::vector<ServerEntityComponentInfo> & comp_info)
  {

  }
};

template <typename ParentType, typename FieldInfo, typename BaseClass, typename BaseConfig>
struct ServerEntityRegisterComponent<ParentType, FieldInfo, ServerEntityComponent<BaseClass, BaseConfig>>
{
  static void Process(std::vector<ServerEntityComponentInfo> & comp_info)
  {
    ServerEntityComponentInfo field_info;
    field_info.m_TypeIdHash = typeid(BaseClass).hash_code();
    field_info.m_TypeNameHash = StormReflTypeInfo<BaseClass>::GetNameHash();
    field_info.m_Get = &FieldInfo::GetFromParent;
    field_info.m_ConstGet = &FieldInfo::GetFromParentConst;
    field_info.m_Cast = static_cast<void * (*)(std::size_t, void *)>(&StormReflTypeInfo<BaseClass>::CastFromTypeIdHash);
    field_info.m_ConstCast = static_cast<const void * (*)(std::size_t, const void *)>(&StormReflTypeInfo<BaseClass>::CastFromTypeIdHash);
    comp_info.push_back(field_info);
  }
};

template <typename Comp>
struct ServerEntitySerializeComponent
{
  static void Serialize(const Comp & comp, ServerEntityNetBitWriter & writer)
  {

  }

  static void Deserialize(Comp & comp, ServerEntityNetBitReader & reader)
  {

  }
};

template <typename BaseClass, typename BaseConfig>
struct ServerEntitySerializeComponent<ServerEntityComponent<BaseClass, BaseConfig>>
{
  static void Serialize(const ServerEntityComponent<BaseClass, BaseConfig> & comp, ServerEntityNetBitWriter & writer)
  {
    comp.Serialize(writer);
  }

  static void Deserialize(ServerEntityComponent<BaseClass, BaseConfig> & comp, ServerEntityNetBitReader & reader)
  {
    comp.Deserialize(reader);
  }
};

template <typename Comp>
void ServerEntityComponentSerialize(const Comp &comp, ServerEntityNetBitWriter &writer)
{
  ServerEntitySerializeComponent<Comp>::Serialize(comp, writer);
}

template <typename Comp>
void ServerEntityComponentDeserialize(Comp &comp, ServerEntityNetBitReader &reader)
{
  ServerEntitySerializeComponent<Comp>::Deserialize(comp, reader);
}

#define DECLARE_SERVER_ENTITY                                                                                                   \
  STORM_REFL;                                                                                                                   \
  STORM_REFL_FUNCS;                                                                                                             \
  static czstr TypeName;                                                                                                        \
  static uint32_t TypeNameHash;                                                                                                 \
  static std::size_t TypeIndex;                                                                                                 \
  static ServerEntityEventDispatch EventDispatch;                                                                               \
                                                                                                                                \
  virtual uint32_t GetTypeNameHash() const override;                                                                            \
  static void RegisterServerEntity();                                                                                           \
                                                                                                                                \
  static bool CanCastToType(uint32_t type_name_hash);                                                                           \
  virtual bool CastToInternal(uint32_t type_name_hash) const override;                                                          \
  virtual NotNullPtr<ServerEntityEventDispatch> GetEventDispatch() override;                                                    \


#define DECLARE_BASE_SERVER_ENTITY                                                                                              \
  STORM_REFL;                                                                                                                   \
  STORM_REFL_FUNCS;                                                                                                             \
  static czstr TypeName;                                                                                                        \
  static uint32_t TypeNameHash;                                                                                                 \
  static std::size_t TypeIndex;                                                                                                 \
  static ServerEntityEventDispatch EventDispatch;                                                                               \
                                                                                                                                \
  virtual uint32_t GetTypeNameHash() const;                                                                                     \
  static void RegisterServerEntity();                                                                                           \
                                                                                                                                \
  static bool CanCastToType(uint32_t type_name_hash);                                                                           \
  virtual bool CastToInternal(uint32_t type_name_hash) const;                                                                   \
  virtual NotNullPtr<ServerEntityEventDispatch> GetEventDispatch();                                                             \


#define REGISTER_SERVER_ENTITY_CODE(ServerEntityName, InitData, InitFunc, BaseClassHash)                                        \
czstr ServerEntityName::TypeName = #ServerEntityName;                                                                           \
uint32_t ServerEntityName::TypeNameHash = COMPILE_TIME_CRC32_STR(#ServerEntityName);                                            \
std::size_t ServerEntityName::TypeIndex = 0;                                                                                    \
ServerEntityEventDispatch ServerEntityName::EventDispatch;                                                                      \
SkipField<ServerEntityName> s_##ServerEntityName##Allocator;                                                                    \
                                                                                                                                \
uint32_t ServerEntityName::GetTypeNameHash() const                                                                              \
{                                                                                                                               \
  return ServerEntityName::TypeNameHash;                                                                                        \
}                                                                                                                               \
                                                                                                                                \
void ServerEntityName::RegisterServerEntity()                                                                                   \
{                                                                                                                               \
  ServerEntityTypeInfo type_info;                                                                                               \
  type_info.m_TypeName = ServerEntityName::TypeName;                                                                            \
  type_info.m_TypeNameHash = ServerEntityName::TypeNameHash;                                                                    \
  type_info.m_InitDataTypeNameHash = COMPILE_TIME_CRC32_STR(#InitData);                                                         \
  type_info.m_TypeIndexPtr = &ServerEntityName::TypeIndex;                                                                      \
                                                                                                                                \
  type_info.m_EntityCreate = []() -> ServerEntity *                                                                             \
  {                                                                                                                             \
    auto ptr = s_##ServerEntityName##Allocator.Allocate();                                                                      \
    return ptr;                                                                                                                 \
  };                                                                                                                            \
                                                                                                                                \
  type_info.m_EntityDuplicate = [](NotNullPtr<const ServerEntity> rhs) -> ServerEntity *                                        \
  {                                                                                                                             \
    auto ptr = s_##ServerEntityName##Allocator.Allocate(*static_cast<const ServerEntityName *>(rhs));                           \
    return ptr;                                                                                                                 \
  };                                                                                                                            \
                                                                                                                                \
  type_info.m_EntityInit = [](NotNullPtr<ServerEntity> entity, NullOptPtr<const ServerEntityInitData> init_data,                \
                              NotNullPtr<GameServerWorld> world)                                                                \
  {                                                                                                                             \
    auto obj = static_cast<ServerEntityName *>(entity);                                                                         \
    obj->m_World = world;                                                                                                       \
    InitFunc                                                                                                                    \
  };                                                                                                                            \
                                                                                                                                \
  type_info.m_EntityCopy = [](NotNullPtr<ServerEntity> entity, NullOptPtr<const ServerEntity> rhs)                              \
  {                                                                                                                             \
    StormReflCopy(*static_cast<ServerEntityName *>(entity), *static_cast<const ServerEntityName *>(rhs));                       \
  };                                                                                                                            \
                                                                                                                                \
  type_info.m_EntityDestroy = [](NotNullPtr<ServerEntity> entity)                                                               \
  {                                                                                                                             \
    s_##ServerEntityName##Allocator.Release(static_cast<ServerEntityName *>(entity));                                           \
  };                                                                                                                            \
                                                                                                                                \
  type_info.m_EntitySerialize = [](NotNullPtr<ServerEntity> entity, ServerEntityNetBitWriter & writer)                          \
  {                                                                                                                             \
    SerializeServerEntity(*static_cast<ServerEntityName *>(entity), writer);                                                    \
  };                                                                                                                            \
                                                                                                                                \
  type_info.m_EntityDeserialize = [](NotNullPtr<ServerEntity> entity, ServerEntityNetBitReader & reader)                        \
  {                                                                                                                             \
    DeserializeServerEntity(*static_cast<ServerEntityName *>(entity), reader);                                                  \
  };                                                                                                                            \
                                                                                                                                \
  type_info.m_ComponentSerialize = [](NotNullPtr<ServerEntity> entity, ServerEntityNetBitWriter & writer)                       \
  {                                                                                                                             \
    StormReflVisitEach(*static_cast<ServerEntityName *>(entity),                                                                \
            [&](auto & field){ ServerEntityComponentSerialize(field.Get(), writer); });                                         \
  };                                                                                                                            \
                                                                                                                                \
  type_info.m_ComponentDeserialize = [](NotNullPtr<ServerEntity> entity, ServerEntityNetBitReader & reader)                     \
  {                                                                                                                             \
    StormReflVisitEach(*static_cast<ServerEntityName *>(entity),                                                                \
            [&](auto & field){ ServerEntityComponentDeserialize(field.Get(), reader); });                                       \
  };                                                                                                                            \
                                                                                                                                \
  type_info.m_AddToUpdateList = [](NotNullPtr<ServerEntity> entity, ServerEntityUpdateList & l)                                 \
  {                                                                                                                             \
    RegisterUpdate(*static_cast<ServerEntityName *>(entity), l);                                                                \
  };                                                                                                                            \
                                                                                                                                \
  StormReflVisitStatic<ServerEntityName>::VisitEach([&](auto field)                                                             \
  {                                                                                                                             \
    using FieldInfoType = decltype(field);                                                                                      \
    using MemberType = typename decltype(field)::member_type;                                                                   \
    ServerEntityRegisterComponent<ServerEntityName, FieldInfoType, MemberType>::Process(type_info.m_ComponentInfo);             \
  });                                                                                                                           \
                                                                                                                                \
  g_ServerEntitySystem.RegisterType(type_info);                                                                                 \
  RegisterServerEntityEvents<ServerEntityName>();                                                                               \
}                                                                                                                               \
                                                                                                                                \
ADD_PREMAIN_CALL(g_ServerEntityRegisterCallList, ServerEntityName, []() { ServerEntityName::RegisterServerEntity(); });         \
                                                                                                                                \
bool ServerEntityName::CanCastToType(uint32_t type_name_hash)                                                                   \
{                                                                                                                               \
  char crap;                                                                                                                    \
  return StormReflTypeInfo<ServerEntityName>::CastFromTypeNameHash(type_name_hash, &crap) != nullptr;                           \
}                                                                                                                               \
                                                                                                                                \
bool ServerEntityName::CastToInternal(uint32_t type_name_hash) const                                                            \
{                                                                                                                               \
  return ServerEntityName::CanCastToType(type_name_hash);                                                                       \
}                                                                                                                               \
                                                                                                                                \
NotNullPtr<ServerEntityEventDispatch> ServerEntityName::GetEventDispatch()                                                      \
{                                                                                                                               \
  return &EventDispatch;                                                                                                        \
}                                                                                                                               \

#define SERVER_ENTITY_CONSTRUCT_NOBASE          0
#define SERVER_ENTITY_CONSTRUCT_BASE(BaseClass) COMPILE_TIME_CRC32_STR(#BaseClass)

#define SERVER_ENTITY_INIT_DATA(InitData)       obj->Init(*static_cast<const InitData *>(init_data));
#define SERVER_ENTITY_NOINIT_DATA   

#define REGISTER_BASE_SERVER_ENTITY(ServerEntityName) \
  REGISTER_SERVER_ENTITY_CODE(ServerEntityName, ServerEntityInitData, SERVER_ENTITY_NOINIT_DATA, SERVER_ENTITY_CONSTRUCT_NOBASE)

#define REGISTER_SERVER_ENTITY(ServerEntityName, BaseClass) \
  REGISTER_SERVER_ENTITY_CODE(ServerEntityName, ServerEntityInitData, SERVER_ENTITY_NOINIT_DATA, SERVER_ENTITY_CONSTRUCT_BASE(BaseClass))

#define REGISTER_SERVER_ENTITY_WITH_INIT_DATA(ServerEntityName, InitData, BaseClass) \
  REGISTER_SERVER_ENTITY_CODE(ServerEntityName, InitData, SERVER_ENTITY_INIT_DATA(InitData), SERVER_ENTITY_CONSTRUCT_BASE(BaseClass)) \
  REGISTER_TYPE(InitData, ServerEntityInitData)

#define SERVER_ENTITY_EVENT_HANDLER STORM_REFL_FUNC
