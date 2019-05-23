#pragma once

#include "Foundation/Common.h"

#include "Engine/Entity/ClientEntityHandle.h"

#include "Runtime/ServerEntity/ServerEntityManager.h"

class GameContainer;
class GameClientInstanceContainer;

class GameClientEntitySync
{
public:
  GameClientEntitySync(GameContainer & game);
  ~GameClientEntitySync();

  void ActivateEntities();
  void Sync(GameClientInstanceContainer & instance_container);
  void DestroyAll();

  NullOptPtr<ClientEntity> FindEntity(int object_index, GameClientInstanceContainer & instance_container);
  void SendEntityEvent(ServerEntityHandle server_object_handle, uint32_t type_name_hash, const void * ev);

private:

  bool IsLocal(NotNullPtr<ServerEntity> server_ent, GameLogicContainer & game_container);
  void SyncEntityList(SparseList<ClientEntityHandle> & entity_list, ServerEntityManager & ent_manager,
                      GameLogicContainer & game_container, bool process_local, bool process_nonlocal);

private:
  GameContainer & m_GameContainer;
  SparseList<ClientEntityHandle> m_HistoryEntities;
  SparseList<ClientEntityHandle> m_CurrentEntities;

  bool m_ActivateEntities = false;
};

