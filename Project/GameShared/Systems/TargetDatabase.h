#pragma once

#include "GameShared/GameSharedCommon.h"
#include "Project/GameServerFramework/GameServerWorld.h"

#include "GameProject/GameServerTypes.h"

#include "Runtime/ServerEntity/ServerEntity.h"

class GameServerEntityBase;
class CollisionDatabase;

class TargetDatabase
{
public:

  void PushTarget(NotNullPtr<GameServerEntityBase> obj, GameServerWorld & game_world);

  std::vector<ServerEntityHandle> QueryForTargets(NotNullPtr<GameServerEntityBase> src, GameNetVal vision_cone_angle,
          GameNetVal vision_distance, const GameNetVec2 & vision_forward, uint32_t collision_mask,
          NullOptPtr<CollisionDatabase> collision_database, GameServerWorld & game_world);

  void Clear();

private:

  struct TargetData
  {
    ServerEntityHandle m_Handle;
    GameNetVec2 m_Position;
    int m_Team;
  };

  std::vector<TargetData> m_Data;
};
