#pragma once

#include "Runtime/RuntimeCommon.h"
#include "Runtime/ServerEntity/ServerObjectUpdate.h"
#include "Runtime/ServerEntity/ServerEntityDef.refl.h"

#include "Foundation/SparseList/SparseList.h"

class ServerEntity;
class ServerEntityInitData;
class ServerEntityHandle;
class GameServerWorld;

struct MapServerEntityHandle;

struct ServerEntityStaticInitData
{
  std::size_t m_TypeIndex;
  ServerEntityInitDataPolyType m_InitData;
  Vector2 m_InitPosition;
  uint32_t m_GUID;
};

struct ServerEntityGuidList
{
  std::unique_ptr<uint32_t[]> m_GUIDs;
};

class ServerEntityManager
{
public:

  ServerEntityManager(const std::vector<ServerEntityStaticInitData> & static_entities,
                      const std::vector<ServerEntityStaticInitData> & dynamic_entities,
                      int max_dynamic_entities, int num_reserved_slots);
  ServerEntityManager(const ServerEntityManager & rhs);

  ~ServerEntityManager();

  ServerEntityManager & operator = (const ServerEntityManager & rhs);

  template <typename T>
  NullOptPtr<T> CreateDynamicEntity(GameServerWorld & game_container, NullOptPtr<ServerEntityInitData> init_data = nullptr)
  {
    auto ptr = CreateDynamicEntityInternal((int)T::TypeIndex, false, init_data, false, game_container);
    return static_cast<T *>(ptr);
  }

  template <typename T>
  NullOptPtr<T> CreateDynamicEntity(std::size_t reserved_slot, GameServerWorld & game_container, NullOptPtr<ServerEntityInitData> init_data = nullptr)
  {
    auto ptr = CreateDynamicEntityInternal((int)T::TypeIndex, (int)reserved_slot, false, init_data, false, game_container);
    return static_cast<T *>(ptr);
  }

  template <typename T>
  NullOptPtr<T> CreateUnsyncedDynamicEntity(GameServerWorld & game_container, NullOptPtr<ServerEntityInitData> init_data = nullptr)
  {
    auto ptr = CreateDynamicEntityInternal((int)T::TypeIndex, -1, true, init_data, false, game_container);
    return static_cast<T *>(ptr);
  }

  template <typename Visitor>
  void VisitEntities(Visitor && visitor)
  {
    std::size_t entity_index = 0;
    for (std::size_t end = m_StaticEntities.size(); entity_index < end; ++entity_index)
    {
      visitor(entity_index, m_StaticEntities[entity_index]);
    }

    for (auto elem : m_DynamicEntities)
    {
      visitor(elem.first + entity_index, elem.second.m_ServerEntity);
    }

    for (auto & elem : m_UnsyncedEntities)
    {
      visitor(-1, elem.m_ServerEntity);
    }
  }

  template <typename Visitor>
  void VisitEntities(Visitor && visitor) const
  {
    std::size_t entity_index = 0;
    for (std::size_t end = m_StaticEntities.size(); entity_index < end; ++entity_index)
    {
      visitor(entity_index, m_StaticEntities[entity_index]);
    }

    for (auto elem : m_DynamicEntities)
    {
      visitor(elem.first + entity_index, elem.second.m_ServerEntity);
    }

    for (auto & elem : m_UnsyncedEntities)
    {
      visitor(-1, elem.m_ServerEntity);
    }
  }

  NullOptPtr<ServerEntity> GetReservedSlotEntity(std::size_t slot_index);

  template <typename T>
  NullOptPtr<T> GetReservedSlotEntityAs(std::size_t slot_index)
  {
    static_assert(std::is_base_of<ServerEntity, T>::value, "Must resolve to server entity type");
    return static_cast<NullOptPtr<T>>(GetReservedSlotEntityInternal(slot_index, T::TypeIndex));
  }

  NullOptPtr<ServerEntity> ResolveMapHandle(const MapServerEntityHandle & handle);

  template <typename T>
  NullOptPtr<T> ResolveMapHandleAs(const MapServerEntityHandle & handle)
  {
    static_assert(std::is_base_of<ServerEntity, T>::value, "Must resolve to server entity type");
    auto ptr = ResolveMapHandle(handle);

    if(ptr)
    {
      return ptr->template CastTo<T>();
    }

    return nullptr;
  }

  void IncrementTimeAlive();
  void CreateUpdateList(ServerEntityUpdateList & update_list);

  int GetHandleBits() const;
  int GetMaxDynamicEntities() const;

  void Serialize(NetBitWriter & writer) const;
  void Deserialize(NetBitReader & reader);

  void StartUpdateLoop();
  bool CompleteUpdateLoop();

protected:

  friend class ServerEntity;
  friend class ServerEntityHandle;

  friend class GameStage;

  void InitAllEntities(const std::vector<ServerEntityStaticInitData> & static_entities,
                      const std::vector<ServerEntityStaticInitData> & dynamic_entities,
                      GameServerWorld & game_container);

  int GetNewDynamicEntityId();
  NullOptPtr<ServerEntity> CreateDynamicEntityInternal(int type_index, bool unsynced,
          NullOptPtr<const ServerEntityInitData> init_data, bool original, GameServerWorld & game_container);
  NullOptPtr<ServerEntity> CreateDynamicEntityInternal(int type_index, int slot_index, bool unsynced,
          NullOptPtr<const ServerEntityInitData> init_data, bool original, GameServerWorld & game_container);
  void DestroyDynamicEntityInternal(NotNullPtr<ServerEntity> ptr);

  void FinalizeHandles();
  NullOptPtr<ServerEntity> ResolveHandle(int slot_index, int gen) const;
  NullOptPtr<ServerEntity> GetReservedSlotEntityInternal(std::size_t slot_index, std::size_t type_index);


  struct DynamicEntityInfo
  {
    NullOptPtr<ServerEntity> m_ServerEntity;
    std::size_t m_TypeIndex;
    bool m_Original;
  };

private:

  std::vector<NotNullPtr<ServerEntity>> m_StaticEntities;
  std::vector<int> m_DynamicEntityGen;
  SparseList<DynamicEntityInfo> m_DynamicEntities;
  std::vector<DynamicEntityInfo> m_UnsyncedEntities;
  std::vector<NotNullPtr<ServerEntity>> m_DeadEntities;

  int m_ReservedSlots;
  int m_MaxDynamicEntities;
  bool m_Initialized;
  bool m_InUpdateLoop;

  std::shared_ptr<ServerEntityGuidList> m_GuidList;
  int m_NumGUIDS;
};

