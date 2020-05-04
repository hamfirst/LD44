
#include "Runtime/RuntimeCommon.h"
#include "Runtime/ServerEntity/ServerEntitySystem.h"
#include "Runtime/ServerEntity/ServerEntity.h"

#include <sb/vector.h>

ServerEntitySystem g_ServerEntitySystem;
PreMainCallList g_ServerEntityRegisterCallList;

NotNullPtr<ServerEntity> ServerEntitySystem::AllocateEntity(std::size_t type_index)
{
  auto entity = m_EntityTypes[type_index].m_EntityCreate();
  entity->m_TypeIndex = (int)type_index;

  return entity;
}

NotNullPtr<ServerEntity> ServerEntitySystem::DuplicateEntity(NotNullPtr<const ServerEntity> rhs)
{
  auto type_index = rhs->m_TypeIndex;
  auto entity = m_EntityTypes[type_index].m_EntityDuplicate(rhs);
  entity->m_TypeIndex = type_index;
  entity->m_EventDispatch = rhs->m_EventDispatch;
  entity->m_FramesAlive = rhs->m_FramesAlive;
  return entity;
}

void ServerEntitySystem::InitEntity(NotNullPtr<ServerEntity> entity, NotNullPtr<const ServerEntityInitData> init_data, GameServerWorld & game_container)
{
  m_EntityTypes[entity->m_TypeIndex].m_EntityInit(entity, init_data, game_container);
}

void ServerEntitySystem::CopyEntity(NotNullPtr<ServerEntity> entity, NotNullPtr<const ServerEntity> rhs)
{
  ASSERT(entity->m_TypeIndex == rhs->m_TypeIndex, "Cannot copy entities of differing types");

  auto type_index = rhs->m_TypeIndex;
  m_EntityTypes[type_index].m_EntityCopy(entity, rhs);
  entity->m_EventDispatch = rhs->m_EventDispatch;
  entity->m_FramesAlive = rhs->m_FramesAlive;
}

void ServerEntitySystem::FreeEntity(NotNullPtr<ServerEntity> entity)
{
  m_EntityTypes[entity->m_TypeIndex].m_EntityDestroy(entity);
}

void ServerEntitySystem::ResetEntityHandles(NotNullPtr<ServerEntity> entity, const ServerEntityManager & obj_manager)
{
  m_EntityTypes[entity->m_TypeIndex].m_EntityResetHandles(entity, obj_manager);
}

void ServerEntitySystem::RegisterType(const ServerEntityTypeInfo & type_info)
{
  m_EntityTypes.emplace_back(type_info);
}

void ServerEntitySystem::FinalizeTypes()
{
  std::sort(m_EntityTypes.begin(), m_EntityTypes.end(), 
    [](const ServerEntityTypeInfo & a, const ServerEntityTypeInfo & b) { return a.m_TypeNameHash < b.m_TypeNameHash; });

  for (std::size_t index = 0, end = m_EntityTypes.size(); index < end; ++index)
  {
    auto & type = m_EntityTypes[index];
    type.m_TypeIndex = (int)index;
    *type.m_TypeIndexPtr = index;
  }

  for (std::size_t index = 0, end = m_EntityTypes.size(); index < end; ++index)
  {
    auto & type = m_EntityTypes[index];
    FinalizeType(type);
  }

  std::vector<uint32_t> processed_types;

  using ItrType = std::unordered_map<uint32_t, std::vector<uint32_t>>::iterator;

  std::unordered_map<uint32_t, std::vector<uint32_t>> dep_list;
  std::unordered_map<uint32_t, std::vector<uint32_t>> rev_list;

  for (auto & type : m_EntityTypes)
  {
    dep_list.emplace(std::make_pair(type.m_TypeNameHash, std::vector<uint32_t>{}));
    rev_list.emplace(std::make_pair(type.m_TypeNameHash, std::vector<uint32_t>{}));
  }

  for (auto & dep : m_EntityDependencies)
  {
    auto itr = dep_list.find(dep.first);
    itr->second.push_back(dep.second);

    itr = rev_list.find(dep.second);
    itr->second.push_back(dep.first);
  }

  m_EntityUpdateIndex.resize(m_EntityTypes.size());

  int update_index = 0;
  while (true)
  {
    std::vector<std::pair<ItrType, ItrType>> nodep_types;
    for (auto & elem : dep_list)
    {
      if (elem.second.size() == 0)
      {
        nodep_types.emplace_back(std::make_pair(dep_list.find(elem.first), rev_list.find(elem.first)));
      }
    }

    std::vector<std::pair<int, uint32_t>> type_ids;
    for (auto & elem : nodep_types)
    {
      for (auto & type : m_EntityTypes)
      {
        if (type.m_TypeNameHash == elem.first->first)
        {
          type_ids.push_back(std::make_pair(type.m_TypeIndex, type.m_TypeNameHash));
          break;
        }
      }
    }

    std::sort(type_ids.begin(), type_ids.end(), [](const std::pair<int, uint32_t> & a, const std::pair<int, uint32_t> & b) { return a.second < b.second; });
    for (auto & elem : type_ids)
    {
      m_EntityUpdateIndex[elem.first] = update_index;
      update_index++;
    }

    for (auto & elem : nodep_types)
    {
      for (auto & rev : elem.second->second)
      {
        auto dep = dep_list.find(rev);
        vremove_quick(dep->second, elem.first->first);
      }

      dep_list.erase(elem.first);
      rev_list.erase(elem.second);
    }

    if (nodep_types.size() == 0)
    {
      break;
    }
  }

  m_EntityDependencies.clear();
}

void ServerEntitySystem::FinalizeType(ServerEntityTypeInfo & type)
{
  auto entity = type.m_EntityCreate();
  auto entity_file = entity->GetDefaultEntityBinding();
  if (entity_file)
  {
    type.m_DefaultEntityFile = entity_file;
  }

  type.m_EntityDestroy(entity);
}

Optional<std::size_t> ServerEntitySystem::GetTypeIndexForInitDataTypeNameHash(uint32_t init_data_type_name_hash)
{
  for (auto & elem : m_EntityTypes)
  {
    if (elem.m_InitDataTypeNameHash == init_data_type_name_hash)
    {
      return elem.m_TypeIndex;
    }
  }

  return {};
}

czstr ServerEntitySystem::GetEntityBindingForInitDataTypeNameHash(uint32_t init_data_type_name_hash)
{
  for (auto & elem : m_EntityTypes)
  {
    if (elem.m_InitDataTypeNameHash == init_data_type_name_hash)
    {
      return elem.m_DefaultEntityFile.size() > 0 ? elem.m_DefaultEntityFile.data() : nullptr;
    }
  }

  return nullptr;
}

const ServerEntityTypeInfo & ServerEntitySystem::GetTypeInfo(int type_index) const
{
  return m_EntityTypes[type_index];
}
