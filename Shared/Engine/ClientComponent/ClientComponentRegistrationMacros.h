#pragma once


#define DECLARE_CLIENT_COMPONENT                                                                                                \
  static czstr TypeName;                                                                                                        \
  static uint32_t TypeNameHash;                                                                                                 \
  static std::size_t TypeIndex;                                                                                                 \
  static const uint32_t * BaseTypes;                                                                                            \
  static uint32_t NumBaseTypes;                                                                                                 \
                                                                                                                                \
  virtual uint32_t GetTypeNameHash() const override;                                                                            \
  static void RegisterComponent();                                                                                              \
  virtual void FinalizeDestroy() override;                                                                                      \
                                                                                                                                \
  static bool CanCastToType(uint32_t type_name_hash);                                                                           \
  virtual bool CastToInternal(uint32_t type_name_hash) const override;                                                          \
                                                                                                                                \
  virtual ClientComponentResolver GetResolver() override;                                                                       \

#define DECLARE_BASE_CLIENT_COMPONENT                                                                                           \
  static czstr TypeName;                                                                                                        \
  static uint32_t TypeNameHash;                                                                                                 \
  static std::size_t TypeIndex;                                                                                                 \
  static const uint32_t * BaseTypes;                                                                                            \
  static uint32_t NumBaseTypes;                                                                                                 \
                                                                                                                                \
  virtual uint32_t GetTypeNameHash() const;                                                                                     \
  static void RegisterComponent();                                                                                              \
  virtual void FinalizeDestroy();                                                                                               \
                                                                                                                                \
  static bool CanCastToType(uint32_t type_name_hash);                                                                           \
  virtual bool CastToInternal(uint32_t type_name_hash) const;                                                                   \
                                                                                                                                \
  virtual ClientComponentResolver GetResolver();                                                                                \


#define REGISTER_CLIENT_COMPONENT_CODE(ComponentName, InitData, ConstructDefault, ConstructInit, BaseClassHash, Base)           \
czstr ComponentName::TypeName = #ComponentName;                                                                                 \
uint32_t ComponentName::TypeNameHash = COMPILE_TIME_CRC32_STR(#ComponentName);                                                  \
std::size_t ComponentName::TypeIndex = 0;                                                                                       \
const uint32_t * ComponentName::BaseTypes = nullptr;                                                                            \
uint32_t ComponentName::NumBaseTypes = 0;                                                                                       \
                                                                                                                                \
uint32_t ComponentName::GetTypeNameHash() const                                                                                 \
{                                                                                                                               \
  return ComponentName::TypeNameHash;                                                                                           \
}                                                                                                                               \
                                                                                                                                \
void ComponentName::RegisterComponent()                                                                                         \
{                                                                                                                               \
  ClientComponentTypeCreationInfo type_info;                                                                                    \
  type_info.m_ComponentTypeNameHash = ComponentName::TypeNameHash;                                                              \
  type_info.m_BaseClassTypeNameHash = BaseClassHash;                                                                            \
  constexpr Hash type_name_hash = COMPILE_TIME_CRC32_STR(#InitData);                                                            \
  type_info.m_InitDataTypeNameHash = type_name_hash;                                                                            \
  type_info.m_BaseListClassesPtr = &ComponentName::BaseTypes;                                                                   \
  type_info.m_NumBaseClassesPtr = &ComponentName::NumBaseTypes;                                                                 \
                                                                                                                                \
  type_info.CreateComponentStore = []() -> void *                                                                               \
  {                                                                                                                             \
    return new ClientComponentList<ComponentName>;                                                                              \
  };                                                                                                                            \
                                                                                                                                \
  type_info.DestroyComponentStore = [](void * comp_store)                                                                       \
  {                                                                                                                             \
    auto store = static_cast<ClientComponentList<ComponentName> *>(comp_store);                                                 \
    delete store;                                                                                                               \
  };                                                                                                                            \
                                                                                                                                \
  type_info.CreateComponent = [](void * comp_store) -> ClientComponent *                                                        \
  {                                                                                                                             \
    auto store = static_cast<ClientComponentList<ComponentName> *>(comp_store);                                                 \
    ConstructDefault;                                                                                                           \
    comp->InitComponentStore(store);                                                                                            \
    return comp;                                                                                                                \
  };                                                                                                                            \
                                                                                                                                \
  type_info.CreateComponentWithInitData = [](void * comp_store, void * init_data) -> ClientComponent *                          \
  {                                                                                                                             \
    auto store = static_cast<ClientComponentList<ComponentName> *>(comp_store);                                                 \
    ConstructInit;                                                                                                              \
    comp->InitComponentStore(store);                                                                                            \
    return comp;                                                                                                                \
  };                                                                                                                            \
                                                                                                                                \
  type_info.FreeComponent = [](void * comp_store, NotNullPtr<ClientComponent> comp)                                             \
  {                                                                                                                             \
    auto store = static_cast<ClientComponentList<ComponentName> *>(comp_store);                                                 \
    store->FreeComponent((ComponentName *)comp);                                                                                \
  };                                                                                                                            \
                                                                                                                                \
  type_info.ResolveHandle = [](void * comp_store, const ClientComponentHandle & handle)                                         \
  {                                                                                                                             \
    auto store = static_cast<ClientComponentList<ComponentName> *>(comp_store);                                                 \
    return store->ResolveHandle(handle);                                                                                        \
  };                                                                                                                            \
                                                                                                                                \
  type_info.AddToUpdateList = [](void * comp_store, ClientComponentUpdateBucketList & l)                                        \
  {                                                                                                                             \
    auto store = static_cast<ClientComponentList<ComponentName> *>(comp_store);                                                 \
    auto visitor = [&](auto & comp)                                                                                             \
    {                                                                                                                           \
      ClientComponentRegisterUpdate(comp, l);                                                                                         \
    };                                                                                                                          \
                                                                                                                                \
    store->VisitAll(visitor);                                                                                                   \
  };                                                                                                                            \
                                                                                                                                \
  type_info.VisitAll = [](void * comp_store, void(*f)(NotNullPtr<ClientComponent>, void *), void * user_data)                   \
  {                                                                                                                             \
    auto store = static_cast<ClientComponentList<ComponentName> *>(comp_store);                                                 \
    auto visitor = [&](auto & comp)                                                                                             \
    {                                                                                                                           \
      f(&comp, user_data);                                                                                                      \
    };                                                                                                                          \
                                                                                                                                \
    store->VisitAll(visitor);                                                                                                   \
  };                                                                                                                            \
                                                                                                                                \
  ComponentName::TypeIndex =                                                                                                    \
    g_ClientComponentTypeSystem.RegisterComponentType(type_info);                                                               \
                                                                                                                                \
  TypeDatabase<ClientComponentInitData>::Get().RegisterType<InitData>();                                                        \
}                                                                                                                               \
                                                                                                                                \
ADD_PREMAIN_CALL(g_ClientComponentRegisterCallList, ComponentName, []() { ComponentName::RegisterComponent(); });               \
                                                                                                                                \
void ComponentName::FinalizeDestroy()                                                                                           \
{                                                                                                                               \
  auto store = static_cast<ClientComponentList<ComponentName> *>(GetComponentSore());                                           \
  store->FreeComponent(this);                                                                                                   \
}                                                                                                                               \
                                                                                                                                \
bool ComponentName::CanCastToType(uint32_t type_name_hash)                                                                      \
{                                                                                                                               \
  for (uint32_t base_type = 0; base_type < ComponentName::NumBaseTypes; ++base_type)                                            \
  {                                                                                                                             \
    if (ComponentName::BaseTypes[base_type] == type_name_hash)                                                                  \
    {                                                                                                                           \
      return true;                                                                                                              \
    }                                                                                                                           \
  }                                                                                                                             \
                                                                                                                                \
  return false;                                                                                                                 \
}                                                                                                                               \
                                                                                                                                \
bool ComponentName::CastToInternal(uint32_t type_name_hash) const                                                               \
{                                                                                                                               \
  return ComponentName::CanCastToType(type_name_hash);                                                                          \
}                                                                                                                               \
                                                                                                                                \
ClientComponentResolver ComponentName::GetResolver()                                                                            \
{                                                                                                                               \
  return [](const ClientComponentHandle & handle, void * comp_store)                                                            \
  {                                                                                                                             \
    auto store = static_cast<ClientComponentList<ComponentName> *>(comp_store);                                                 \
    return store->ResolveHandle(handle);                                                                                        \
  };                                                                                                                            \
}                                                                                                                               \

#define CLIENT_COMPONENT_CONSTRUCT_NOBASE
#define CLIENT_COMPONENT_CONSTRUCT_BASE(BaseClass) , BaseClass

#define CLIENT_COMPONENT_CONSTRUCT_NOINIT_DEFAULT auto comp = store->AllocateComponent();
#define CLIENT_COMPONENT_CONSTRUCT_NOINIT_DATA    auto comp = store->AllocateComponent();

#define CLIENT_COMPONENT_CONSTRUCT_INIT_DEFAULT(InitData) InitData init_data = {}; auto comp = store->AllocateComponent(std::move(init_data));
#define CLIENT_COMPONENT_CONSTRUCT_INIT_DATA(InitData)    auto comp = store->AllocateComponent(std::move(*((InitData *)init_data)));

#define REGISTER_BASE_CLIENT_COMPONENT(ComponentName) \
  REGISTER_CLIENT_COMPONENT_CODE(ComponentName, ClientComponentInitData, CLIENT_COMPONENT_CONSTRUCT_NOINIT_DEFAULT, CLIENT_COMPONENT_CONSTRUCT_NOINIT_DATA, 0, CLIENT_COMPONENT_CONSTRUCT_NOBASE)

#define REGISTER_CLIENT_COMPONENT(ComponentName, BaseClass) \
  REGISTER_CLIENT_COMPONENT_CODE(ComponentName, ClientComponentInitData, CLIENT_COMPONENT_CONSTRUCT_NOINIT_DEFAULT, CLIENT_COMPONENT_CONSTRUCT_NOINIT_DATA, BaseClass::TypeNameHash, CLIENT_COMPONENT_CONSTRUCT_BASE(BaseClass))

#define REGISTER_CLIENT_COMPONENT_WITH_INIT_DATA(ComponentName, InitData, BaseClass) \
  REGISTER_CLIENT_COMPONENT_CODE(ComponentName, InitData, CLIENT_COMPONENT_CONSTRUCT_INIT_DEFAULT(InitData), CLIENT_COMPONENT_CONSTRUCT_INIT_DATA(InitData), BaseClass::TypeNameHash, CLIENT_COMPONENT_CONSTRUCT_BASE(BaseClass))
