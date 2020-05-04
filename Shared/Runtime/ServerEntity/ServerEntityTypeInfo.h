
#pragma once

#include "Runtime/RuntimeCommon.h"

class ServerEntity;
class ServerEntityManager;
class ServerEntityInitData;
class ServerEntityUpdateList;
class ServerEntityNetBitWriter;
class ServerEntityNetBitReader;

class GameServerWorld;

struct ServerEntityComponentInfo
{
  uint32_t m_TypeNameHash;
  std::size_t m_TypeIdHash;

  void * (*m_Get)(void *);
  const void * (*m_ConstGet)(const void *);
  void * (*m_Cast)(std::size_t, void *);
  const void * (*m_ConstCast)(std::size_t, const void *);
};

struct ServerEntityTypeInfo
{
  uint32_t m_TypeNameHash;
  uint32_t m_TypeIndex;
  uint32_t m_InitDataTypeNameHash;
  NotNullPtr<std::size_t> m_TypeIndexPtr;

  std::vector<ServerEntityComponentInfo> m_ComponentInfo;

  NotNullPtr<ServerEntity>(*m_EntityCreate)();
  NotNullPtr<ServerEntity>(*m_EntityDuplicate)(NotNullPtr<const ServerEntity> rhs);

  void(*m_EntityInit)(NotNullPtr<ServerEntity> entity, NullOptPtr<const ServerEntityInitData> init_data,
                      GameServerWorld & game_container);
  void(*m_EntityCopy)(NotNullPtr<ServerEntity> entity, NotNullPtr<const ServerEntity> rhs);
  void(*m_EntityResetHandles)(NotNullPtr<ServerEntity> entity, const ServerEntityManager & obj_manager);
  void(*m_EntityDestroy)(NotNullPtr<ServerEntity> entity);
  void(*m_AddToUpdateList)(NotNullPtr<ServerEntity> entity, ServerEntityUpdateList & l);

  void(*m_EntitySerialize)(NotNullPtr<ServerEntity> entity, ServerEntityNetBitWriter & writer);
  void(*m_EntityDeserialize)(NotNullPtr<ServerEntity> entity, ServerEntityNetBitReader & reader);
  void(*m_ComponentSerialize)(NotNullPtr<ServerEntity> entity, ServerEntityNetBitWriter & writer);
  void(*m_ComponentDeserialize)(NotNullPtr<ServerEntity> entity, ServerEntityNetBitReader & reader);

  std::string m_DefaultEntityFile;
};


