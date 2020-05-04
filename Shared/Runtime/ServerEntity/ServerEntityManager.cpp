
#include "Runtime/RuntimeCommon.h"
#include "Runtime/ServerEntity/ServerEntityManager.h"
#include "Runtime/ServerEntity/ServerEntitySystem.h"
#include "Runtime/ServerEntity/ServerEntity.h"
#include "Runtime/ServerEntity/ServerEntitySerialize.h"
#include "Runtime/Map/MapHandles.refl.h"

#include "StormNet/NetBitUtil.h"

ServerEntityManager::ServerEntityManager(const std::vector<ServerEntityStaticInitData> & static_entities,
                                         const std::vector<ServerEntityStaticInitData> & dynamic_entities,
                                         int max_dynamic_entities, int num_reserved_slots)
{
  m_Initialized = false;
  m_InUpdateLoop = false;

  m_NumGUIDS = static_entities.size() + max_dynamic_entities;
  m_GuidList = std::make_shared<ServerEntityGuidList>(ServerEntityGuidList{ std::make_unique<uint32_t[]>(m_NumGUIDS) });

  int slot_index = 0;
  for (auto & obj : static_entities)
  {
    auto ptr = g_ServerEntitySystem.AllocateEntity(obj.m_TypeIndex);
    ptr->m_IsStatic = true;
    ptr->m_TypeIndex = (int)obj.m_TypeIndex;
    ptr->m_SlotIndex = -1;
    ptr->m_FramesAlive = 0;
    ptr->m_ServerEntityHandle.m_SlotId = slot_index;
    ptr->m_ServerEntityHandle.m_Gen = 0;
    ptr->m_EventDispatch = ptr->GetEventDispatch();
    m_StaticEntities.emplace_back(ptr);

    m_GuidList->m_GUIDs[slot_index] = obj.m_GUID;

    ++slot_index;
  }

  m_ReservedSlots = num_reserved_slots;
  m_MaxDynamicEntities = max_dynamic_entities;

  m_DynamicEntityGen.resize(max_dynamic_entities);
  m_DynamicEntities.Reserve(max_dynamic_entities);

  slot_index = num_reserved_slots;

  for (auto & obj : dynamic_entities)
  {
    auto dynamic_slot_index = static_entities.size() + slot_index;
    auto ptr = g_ServerEntitySystem.AllocateEntity((int)obj.m_TypeIndex);
    ptr->m_IsStatic = false;
    ptr->m_TypeIndex = (int)obj.m_TypeIndex;
    ptr->m_SlotIndex = slot_index;
    ptr->m_ServerEntityHandle.m_SlotId = slot_index + (int)m_StaticEntities.size();
    ptr->m_ServerEntityHandle.m_Gen = m_DynamicEntityGen[slot_index];
    ptr->m_EventDispatch = ptr->GetEventDispatch();

    m_DynamicEntities.EmplaceAt(dynamic_slot_index, DynamicEntityInfo{ptr, obj.m_TypeIndex, true});
    m_GuidList->m_GUIDs[dynamic_slot_index] = obj.m_GUID;

    ++slot_index;
  }
}

ServerEntityManager::ServerEntityManager(const ServerEntityManager & rhs)
{
  m_StaticEntities.reserve(rhs.m_StaticEntities.size());

  for (auto & obj : rhs.m_StaticEntities)
  {
    auto ptr = g_ServerEntitySystem.DuplicateEntity(obj);
    ptr->m_SlotIndex = -1;
    m_StaticEntities.emplace_back(ptr);
  }

  m_DynamicEntityGen = rhs.m_DynamicEntityGen;
  m_DynamicEntities.Reserve(rhs.m_DynamicEntities.Size());

  for (auto obj : rhs.m_DynamicEntities)
  {
    auto ptr = g_ServerEntitySystem.DuplicateEntity(obj.second.m_ServerEntity);
    ptr->m_SlotIndex = (int)obj.first;
    m_DynamicEntities.EmplaceAt(obj.first, DynamicEntityInfo{ ptr, obj.second.m_TypeIndex, obj.second.m_Original });
  }

  for (auto obj : rhs.m_UnsyncedEntities)
  {
    auto ptr = g_ServerEntitySystem.DuplicateEntity(obj.m_ServerEntity);
    ptr->m_SlotIndex = -1;
    m_UnsyncedEntities.emplace_back(DynamicEntityInfo{ ptr, obj.m_TypeIndex, obj.m_Original });
  }

  m_Initialized = rhs.m_Initialized;
  m_ReservedSlots = rhs.m_ReservedSlots;
  m_MaxDynamicEntities = rhs.m_MaxDynamicEntities;

  m_GuidList = rhs.m_GuidList;
  m_NumGUIDS = rhs.m_NumGUIDS;

  m_InUpdateLoop = false;
}

ServerEntityManager::~ServerEntityManager()
{
  for (auto & obj : m_StaticEntities)
  {
      g_ServerEntitySystem.FreeEntity(obj);
  }

  for (auto obj : m_DynamicEntities)
  {
      g_ServerEntitySystem.FreeEntity(obj.second.m_ServerEntity);
  }
}

ServerEntityManager & ServerEntityManager::operator = (const ServerEntityManager & rhs)
{
  ASSERT(m_StaticEntities.size() == rhs.m_StaticEntities.size(), "Bad copy of ServerEntityManager");
  ASSERT(m_MaxDynamicEntities == rhs.m_MaxDynamicEntities, "Bad copy of ServerEntityManager");
  ASSERT(m_ReservedSlots == rhs.m_ReservedSlots, "Bad copy of ServerEntityManager");

  for(std::size_t index = 0, end = m_StaticEntities.size(); index < end; ++index)
  {
      g_ServerEntitySystem.CopyEntity(m_StaticEntities[index], rhs.m_StaticEntities[index]);
  }

  for (std::size_t index = 0, end = m_MaxDynamicEntities; index < end; ++index)
  {
    if (rhs.m_DynamicEntities.HasAt(index))
    {
      if (m_DynamicEntities.HasAt(index))
      {
        if (m_DynamicEntities[index].m_TypeIndex == rhs.m_DynamicEntities[index].m_TypeIndex)
        {
            g_ServerEntitySystem.CopyEntity(m_DynamicEntities[index].m_ServerEntity, rhs.m_DynamicEntities[index].m_ServerEntity);
          continue;
        }

        m_DynamicEntities[index].m_ServerEntity->Destroy(*this);
      }

      auto ptr = g_ServerEntitySystem.DuplicateEntity(rhs.m_DynamicEntities[index].m_ServerEntity);
      ptr->m_SlotIndex = (int)index;
      m_DynamicEntities.EmplaceAt(index, DynamicEntityInfo{ ptr, rhs.m_DynamicEntities[index].m_TypeIndex });
    }
    else
    {
      if (m_DynamicEntities.HasAt(index))
      {
        m_DynamicEntities[index].m_ServerEntity->Destroy(*this);
      }
    }
  }

  for(auto & obj : m_UnsyncedEntities)
  {
      g_ServerEntitySystem.FreeEntity(obj.m_ServerEntity);
  }

  m_UnsyncedEntities.clear();

  for (auto obj : rhs.m_UnsyncedEntities)
  {
    auto ptr = g_ServerEntitySystem.DuplicateEntity(obj.m_ServerEntity);
    ptr->m_SlotIndex = -1;
    ptr->m_IsUnsynced = true;
    m_UnsyncedEntities.emplace_back(DynamicEntityInfo{ ptr, obj.m_TypeIndex, obj.m_Original });
  }

  m_Initialized = rhs.m_Initialized;
  m_ReservedSlots = rhs.m_ReservedSlots;
  m_MaxDynamicEntities = rhs.m_MaxDynamicEntities;

  return *this;
}

NullOptPtr<ServerEntity> ServerEntityManager::GetReservedSlotEntity(std::size_t slot_index)
{
  if (slot_index >= m_ReservedSlots)
  {
    return nullptr;
  }

  auto dynamic_entity_info = m_DynamicEntities.TryGet(slot_index);
  return dynamic_entity_info ? dynamic_entity_info->m_ServerEntity : nullptr;
}

NullOptPtr<ServerEntity> ServerEntityManager::ResolveMapHandle(const MapServerEntityHandle & handle)
{
  uint32_t guid = handle.m_GUID;

  int slot_index = -1;
  for(int index = 0; index < m_NumGUIDS; ++index)
  {
    if(m_GuidList->m_GUIDs[index] == guid)
    {
      slot_index = index;
      break;
    }
  }

  if(slot_index < 0)
  {
    return nullptr;
  }

  if (slot_index < (int)m_StaticEntities.size())
  {
    return const_cast<ServerEntity *>(m_StaticEntities[slot_index]);
  }

  slot_index -= (int)m_StaticEntities.size();
  if (m_DynamicEntities[slot_index].m_Original == false)
  {
    return nullptr;
  }

  auto ptr = m_DynamicEntities.TryGet(slot_index);
  return ptr ? const_cast<ServerEntity *>(ptr->m_ServerEntity) : nullptr;
}

void ServerEntityManager::IncrementTimeAlive()
{
  for (auto & obj : m_StaticEntities)
  {
    obj->m_FramesAlive++;
  }

  for (auto obj : m_DynamicEntities)
  {
    obj.second.m_ServerEntity->m_FramesAlive++;
  }

  for (auto & obj : m_UnsyncedEntities)
  {
    obj.m_ServerEntity->m_FramesAlive++;
  }
}

void ServerEntityManager::CreateUpdateList(ServerEntityUpdateList & update_list)
{
  std::vector<std::pair<int, NotNullPtr<ServerEntity>>> update_objs;
  update_objs.reserve(m_StaticEntities.size() + m_DynamicEntities.Size());

  for (auto & obj : m_StaticEntities)
  {
    update_objs.emplace_back(std::make_pair(obj->m_TypeIndex, obj));
  }

  for (auto obj : m_DynamicEntities)
  {
    auto ptr = obj.second.m_ServerEntity;
    update_objs.emplace_back(std::make_pair(ptr->m_TypeIndex, ptr));
  }

  for (auto & obj : m_UnsyncedEntities)
  {
    auto ptr = obj.m_ServerEntity;
    update_objs.emplace_back(std::make_pair(ptr->m_TypeIndex, ptr));
  }

  std::sort(update_objs.begin(), update_objs.end(), 
    [](const std::pair<int, NotNullPtr<ServerEntity>> & a, std::pair<int, NotNullPtr<ServerEntity>> & b) 
    {
      return a.first < b.first;
    });

  for (auto & elem : update_objs)
  {
    g_ServerEntitySystem.m_EntityTypes[elem.first].m_AddToUpdateList(elem.second, update_list);
  }
}

int ServerEntityManager::GetHandleBits() const
{
  return GetRequiredBits(m_StaticEntities.size() + m_MaxDynamicEntities);
}

int ServerEntityManager::GetMaxDynamicEntities() const
{
  return m_MaxDynamicEntities;
}

void ServerEntityManager::Serialize(NetBitWriter & writer) const
{
  ServerEntityNetBitWriter so_writer(writer, this);
  writer.WriteBits(m_Initialized, 1);
  for (auto & obj : m_StaticEntities)
  {
    auto type_index = obj->m_TypeIndex;
    g_ServerEntitySystem.m_EntityTypes[type_index].m_EntitySerialize(obj, so_writer);
    g_ServerEntitySystem.m_EntityTypes[type_index].m_ComponentSerialize(obj, so_writer);
  }

  for (std::size_t index = 0; index < m_MaxDynamicEntities; ++index)
  {
    auto obj = m_DynamicEntities.TryGet(index);

    if (obj)
    {
      so_writer.WriteBits(1, 1);

      auto type_index = obj->m_TypeIndex;
      so_writer.WriteBits(type_index, GetRequiredBits(g_ServerEntitySystem.m_EntityTypes.size() - 1));

      auto original = obj->m_Original;
      so_writer.WriteBits(original ? 1 : 0, 1);

      auto lifetime = std::min(7, obj->m_ServerEntity->m_FramesAlive);
      so_writer.WriteBits((uint64_t)lifetime, 3);

      g_ServerEntitySystem.m_EntityTypes[type_index].m_EntitySerialize(obj->m_ServerEntity, so_writer);
      g_ServerEntitySystem.m_EntityTypes[type_index].m_ComponentSerialize(obj->m_ServerEntity, so_writer);
    }
    else
    {
      so_writer.WriteBits(0, 1);
    }
  }
}

void ServerEntityManager::Deserialize(NetBitReader & reader)
{
  ServerEntityNetBitReader so_reader(reader, this);
  m_Initialized = reader.ReadUBits(1) != 0;

  for (auto & obj : m_StaticEntities)
  {
    auto type_index = obj->m_TypeIndex;
    g_ServerEntitySystem.m_EntityTypes[type_index].m_EntityDeserialize(obj, so_reader);
    obj->InitStaticComponents();
    g_ServerEntitySystem.m_EntityTypes[type_index].m_ComponentDeserialize(obj, so_reader);
  }

  for (std::size_t slot_index = 0; slot_index < m_MaxDynamicEntities; ++slot_index)
  {
    auto valid = so_reader.ReadUBits(1);
    auto obj = m_DynamicEntities.TryGet(slot_index);

    if (valid)
    {
      auto type_index = so_reader.ReadUBits(GetRequiredBits(g_ServerEntitySystem.m_EntityTypes.size() - 1));
      auto original = so_reader.ReadUBits(1) != 0;
      auto lifetime = so_reader.ReadUBits(3);

      if (obj)
      {
        if (obj->m_TypeIndex == type_index)
        {
          g_ServerEntitySystem.m_EntityTypes[type_index].m_EntityDeserialize(obj->m_ServerEntity, so_reader);
          obj->m_ServerEntity->m_FramesAlive = (int)lifetime;
          obj->m_Original = original;

          obj->m_ServerEntity->InitStaticComponents();
          g_ServerEntitySystem.m_EntityTypes[type_index].m_ComponentDeserialize(obj->m_ServerEntity, so_reader);
          continue;
        }
        
        obj->m_ServerEntity->Destroy(*this);
      }

      auto ptr = g_ServerEntitySystem.AllocateEntity(type_index);
      ptr->m_IsStatic = false;
      ptr->m_TypeIndex = (int)type_index;
      ptr->m_SlotIndex = (int)slot_index;
      ptr->m_ServerEntityHandle.m_SlotId = (int)slot_index + (int)m_StaticEntities.size();
      ptr->m_ServerEntityHandle.m_Gen = m_DynamicEntityGen[slot_index];
      ptr->m_EventDispatch = ptr->GetEventDispatch();
      ptr->m_FramesAlive = (int)lifetime;

      m_DynamicEntities.EmplaceAt((std::size_t)slot_index, DynamicEntityInfo{ptr, (std::size_t)type_index, original});

      g_ServerEntitySystem.m_EntityTypes[type_index].m_EntityDeserialize(ptr, so_reader);
      ptr->InitStaticComponents();
      g_ServerEntitySystem.m_EntityTypes[type_index].m_ComponentDeserialize(ptr, so_reader);
    }
    else
    {
      if (obj)
      {
        obj->m_ServerEntity->Destroy(*this);
      }
    }
  }
}

void ServerEntityManager::StartUpdateLoop()
{
  ASSERT(m_InUpdateLoop == false, "Recursive update loop!");
  m_InUpdateLoop = true;
}

bool ServerEntityManager::CompleteUpdateLoop()
{
  ASSERT(m_InUpdateLoop == true, "Not in update loop!");
  m_InUpdateLoop = false;

  if(m_DeadEntities.empty())
  {
    return false;
  }

  for(auto & elem : m_DeadEntities)
  {
    DestroyDynamicEntityInternal(elem);
  }

  m_DeadEntities.clear();
  return true;
}

void ServerEntityManager::InitAllEntities(
        const std::vector<ServerEntityStaticInitData> & static_entities,
        const std::vector<ServerEntityStaticInitData> & dynamic_entities,
        GameServerWorld & game_container)
{
  if(m_Initialized)
  {
    return;
  }

  int slot_index = 0;
  for (auto & obj : static_entities)
  {
    auto type_index = m_StaticEntities[slot_index]->m_TypeIndex;
    g_ServerEntitySystem.m_EntityTypes[type_index].m_EntityInit(m_StaticEntities[slot_index],
      obj.m_InitData.GetValue(), game_container);

    m_StaticEntities[slot_index]->InitPosition(obj.m_InitPosition);
    m_StaticEntities[slot_index]->InitStaticComponents();
    ++slot_index;
  }

  slot_index = m_ReservedSlots;
  for (auto & obj : dynamic_entities)
  {
    auto ptr = m_DynamicEntities[slot_index].m_ServerEntity;
    if (ptr && m_DynamicEntities[slot_index].m_Original)
    {
      auto type_index = ptr->m_TypeIndex;

      g_ServerEntitySystem.m_EntityTypes[type_index].m_EntityInit(ptr,
        obj.m_InitData.GetValue(), game_container);

      ptr->InitPosition(obj.m_InitPosition);
      ptr->InitStaticComponents();
    }

    ++slot_index;
  }

  m_Initialized = true;
}

int ServerEntityManager::GetNewDynamicEntityId()
{
  for (std::size_t index = m_ReservedSlots, end = m_MaxDynamicEntities; index < end; index++)
  {
    if (m_DynamicEntities.HasAt(index) == false)
    {
      return (int)index;
    }
  }

  return -1;
}

NullOptPtr<ServerEntity> ServerEntityManager::CreateDynamicEntityInternal(int type_index, bool unsynced,
        NullOptPtr<const ServerEntityInitData> init_data, bool original, GameServerWorld & game_container)
{
  auto slot_index = GetNewDynamicEntityId();
  if (slot_index == -1)
  {
    return nullptr;
  }

  return CreateDynamicEntityInternal(type_index, slot_index, unsynced, init_data, original, game_container);
}

NullOptPtr<ServerEntity> ServerEntityManager::CreateDynamicEntityInternal(int type_index, int slot_index, bool unsynced,
        NullOptPtr<const ServerEntityInitData> init_data, bool original, GameServerWorld & game_container)
{
  auto ptr = g_ServerEntitySystem.AllocateEntity(type_index);
  ptr->m_IsStatic = false;
  ptr->m_IsUnsynced = unsynced;
  ptr->m_TypeIndex = type_index;
  ptr->m_SlotIndex = slot_index;
  ptr->m_EventDispatch = ptr->GetEventDispatch();

  if(unsynced == false)
  {
    ptr->m_ServerEntityHandle.m_SlotId = slot_index + (int) m_StaticEntities.size();
    ptr->m_ServerEntityHandle.m_Gen = m_DynamicEntityGen[slot_index];

    m_DynamicEntities.EmplaceAt((std::size_t)slot_index, DynamicEntityInfo{ptr, (std::size_t)type_index, original});
  }
  else
  {
    ptr->m_ServerEntityHandle.m_SlotId = -1;
    ptr->m_ServerEntityHandle.m_Gen = 0;

    m_UnsyncedEntities.emplace_back(DynamicEntityInfo{ptr, (std::size_t)type_index, false});
  }

  if(m_Initialized)
  {
    g_ServerEntitySystem.InitEntity(ptr, init_data, game_container);
    ptr->InitStaticComponents();
  }

  return ptr;
}

void ServerEntityManager::DestroyDynamicEntityInternal(NotNullPtr<ServerEntity> ptr)
{
  if(m_InUpdateLoop)
  {
    ptr->m_IsDestroyed = true;
    m_DeadEntities.push_back(ptr);
    return;
  }

  if(ptr->m_IsUnsynced)
  {
    for(std::size_t index = 0, end = m_UnsyncedEntities.size(); index < end; ++index)
    {
      auto & elem = m_UnsyncedEntities[index];
      if(elem.m_ServerEntity == ptr)
      {
        g_ServerEntitySystem.FreeEntity(elem.m_ServerEntity);
        vremove_index_quick(m_UnsyncedEntities, index);
        return;
      }
    }
    ASSERT(false, "Attempting to delete unsynced entity that was not in the entity list");
    return;
  }

  auto slot_index = ptr->m_ServerEntityHandle.m_SlotId - m_StaticEntities.size();
  ASSERT(slot_index >= 0, "Attempting to free a static entity");

  if (m_DynamicEntities.HasAt(slot_index) == false)
  {
    ASSERT(slot_index >= 0, "Attempting to free an already freed entity");
    return;
  }

  m_DynamicEntityGen[slot_index]++;
  
  g_ServerEntitySystem.FreeEntity(m_DynamicEntities[slot_index].m_ServerEntity);
  m_DynamicEntities.RemoveAt(slot_index);
}

void ServerEntityManager::FinalizeHandles()
{
  for (auto & obj : m_StaticEntities)
  {
    g_ServerEntitySystem.ResetEntityHandles(obj, *this);
  }

  for (auto obj : m_DynamicEntities)
  {
    g_ServerEntitySystem.ResetEntityHandles(obj.second.m_ServerEntity, *this);
  }

  for (auto & obj : m_UnsyncedEntities)
  {
    g_ServerEntitySystem.ResetEntityHandles(obj.m_ServerEntity, *this);
  }

  for (auto & gen : m_DynamicEntityGen)
  {
    gen = 0;
  }

}

NullOptPtr<ServerEntity> ServerEntityManager::ResolveHandle(int slot_index, int gen) const
{
  if (slot_index < 0)
  {
    return nullptr;
  }

  NullOptPtr<ServerEntity> out_obj = nullptr;
  if (slot_index < (int)m_StaticEntities.size())
  {
    if (gen != 0)
    {
      return nullptr;
    }

    out_obj = m_StaticEntities[slot_index];
  }
  else
  {
    slot_index -= (int) m_StaticEntities.size();
    if (m_DynamicEntityGen[slot_index] != gen)
    {
      return nullptr;
    }

    auto ptr = m_DynamicEntities.TryGet(slot_index);
    out_obj = ptr ? ptr->m_ServerEntity : nullptr;
  }

  if(out_obj && out_obj->m_IsDestroyed)
  {
    return nullptr;
  }

  return out_obj;
}

NullOptPtr<ServerEntity> ServerEntityManager::GetReservedSlotEntityInternal(std::size_t slot_index, std::size_t type_index)
{
  if (slot_index >= m_ReservedSlots)
  {
    return nullptr;
  }

  auto dynamic_entity_info = m_DynamicEntities.TryGet(slot_index);
  return dynamic_entity_info && dynamic_entity_info->m_TypeIndex == type_index ? dynamic_entity_info->m_ServerEntity : nullptr;
}

