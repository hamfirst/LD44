#pragma once

#include "Foundation/CallList/CallList.h"

#include "Runtime/RuntimeCommon.h"
#include "Runtime/ServerEntity/ServerEntityTypeInfo.h"

class ServerEntitySystem
{
public:

  void RegisterType(const ServerEntityTypeInfo & type_info);
  void FinalizeTypes();

  Optional<std::size_t> GetTypeIndexForInitDataTypeNameHash(uint32_t init_data_type_name_hash);
  czstr GetEntityBindingForInitDataTypeNameHash(uint32_t init_data_type_name_hash);

  const ServerEntityTypeInfo & GetTypeInfo(int type_index) const;
  const std::vector<ServerEntityTypeInfo> & GetAllTypes() const;

private:

  friend class ServerEntityManager;

  NotNullPtr<ServerEntity> AllocateEntity(std::size_t type_index);
  NotNullPtr<ServerEntity> DuplicateEntity(NotNullPtr<const ServerEntity> rhs);

  void InitEntity(NotNullPtr<ServerEntity> entity, NotNullPtr<const ServerEntityInitData> init_data, NotNullPtr<GameServerWorld> game_world);
  void CopyEntity(NotNullPtr<ServerEntity> entity, NotNullPtr<const ServerEntity> rhs);
  void FreeEntity(NotNullPtr<ServerEntity> entity);
  void FinalizeType(ServerEntityTypeInfo & type);
  
private:

  std::vector<ServerEntityTypeInfo> m_EntityTypes;

  std::vector<std::pair<uint32_t, uint32_t>> m_EntityDependencies;
  std::vector<int> m_EntityUpdateIndex;
};

extern ServerEntitySystem g_ServerEntitySystem;
extern PreMainCallList g_ServerEntityRegisterCallList;