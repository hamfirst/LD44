#pragma once

#include "Foundation/CallList/CallList.h"

#include "Engine/ClientComponent/ClientComponent.h"

class ClientComponentUpdateBucketList;
class PropertyFieldDatabase;

struct ClientComponentTypeCreationInfo
{
  uint32_t m_ComponentTypeNameHash;
  uint32_t m_BaseClassTypeNameHash;
  uint32_t m_InitDataTypeNameHash;

  NotNullPtr<const uint32_t *> m_BaseListClassesPtr;
  NotNullPtr<uint32_t> m_NumBaseClassesPtr;

  void * (*CreateComponentStore)();
  void (*DestroyComponentStore)(void *);

  NotNullPtr<ClientComponent>(*CreateComponent)(void *);
  NotNullPtr<ClientComponent>(*CreateComponentWithInitData)(void *, void *);
  void(*FreeComponent)(void *, NotNullPtr<ClientComponent>);
  NullOptPtr<ClientComponent>(*ResolveHandle)(void *, const ClientComponentHandle &);

  void (*AddToUpdateList)(void *, ClientComponentUpdateBucketList &);
  void(*VisitAll)(void *, void(*)(NotNullPtr<ClientComponent>, void *), void *);
  std::vector<uint32_t> m_BaseClassList;
};

class ENGINE_EXPORT ClientComponentTypeSystem
{
public:
  ClientComponentTypeSystem();
  ~ClientComponentTypeSystem();

  std::size_t RegisterComponentType(const ClientComponentTypeCreationInfo & comp_info);
  void SetComponentUpdateOrdering(uint32_t pre_type_name_hash, uint32_t post_type_name_hash);
  void FinalizeComponentSystem();
  void LoadPropertyDatabase(PropertyFieldDatabase & property_db);

private:
  
  friend class ClientComponentSystem;

  std::vector<ClientComponentTypeCreationInfo> m_ComponentInfo;
  std::unordered_map<uint32_t, std::size_t> m_ComponentTypeLookup;
  std::vector<std::pair<uint32_t, uint32_t>> m_UpdateReqs;
  std::vector<std::pair<std::size_t, void(*)(void *, ClientComponentUpdateBucketList &)>> m_ComponentUpdate;
};

class ENGINE_EXPORT ClientComponentSystem
{
public:

  ClientComponentSystem();
  ~ClientComponentSystem();

  void CreateUpdateBucketList(ClientComponentUpdateBucketList & bucket_list);
  void FinalizeComponentDestroys();

protected:

  friend class ClientComponent;
  friend class ClientEntity;
  friend class ClientEntitySystem;
  friend class EngineState;

  NullOptPtr<ClientComponent> CreateComponent(std::size_t type_index, void * init_data);
  NullOptPtr<ClientComponent> CreateComponentFromTypeNameHash(uint32_t type_name_hash, void * init_data);

  void VisitComponents(uint32_t type_name_hash, void(*callback)(NotNullPtr<ClientComponent>, void *), void * user_data);

  void AddToDeadComponentList(NotNullPtr<ClientComponent> comp);

private:

  std::vector<void *> m_ComponentStores;
  std::vector<NotNullPtr<ClientComponent>> m_DeadComponents;
};

extern ENGINE_EXPORT ClientComponentTypeSystem g_ClientComponentTypeSystem;
extern ENGINE_EXPORT PreMainCallList g_ClientComponentRegisterCallList;
extern ENGINE_EXPORT PreMainCallList g_ClientComponentUpdateDepRegisterCallList;
