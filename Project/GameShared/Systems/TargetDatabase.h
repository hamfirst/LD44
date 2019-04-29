#pragma once

#include "GameShared/GameSharedCommon.h"
#include "GameShared/GameLogicContainer.h"

#include "Game/GameServerTypes.h"

#include "Runtime/ServerObject/ServerObject.h"

class GameServerObjectBase;
class CollisionDatabase;

class TargetDatabase
{
public:

  void PushTarget(NotNullPtr<GameServerObjectBase> obj, GameLogicContainer & game_container);

  std::vector<ServerObjectHandle> QueryForTargets(NotNullPtr<GameServerObjectBase> src, GameNetVal vision_cone_angle,
          GameNetVal vision_distance, const GameNetVec2 & vision_forward, uint32_t collision_mask,
          NullOptPtr<CollisionDatabase> collision_database, GameLogicContainer & game_container);

  void Clear();

private:

  struct TargetData
  {
    ServerObjectHandle m_Handle;
    GameNetVec2 m_Position;
    int m_Team;
  };

  std::vector<TargetData> m_Data;
};
