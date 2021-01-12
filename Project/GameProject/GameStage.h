#pragma once

#include "Runtime/Map/MapResource.h"

#include "Foundation/Pathfinding/GraphPathfinding.h"
#include "Foundation/Pathfinding/GridPathfinding.h"
#include "Foundation/Pathfinding/PathfindingPath.h"

#include "GameProject/GameFullState.refl.h"
#include "GameProject/GameServerTypes.h"

#include "GameProject/Data/KillVolume.refl.h"

#include "Runtime/Collision/CollisionDatabase.h"
#include "Runtime/Collision/IntersectionDatabase.h"
#include "Runtime/Map/MapHandles.refl.h"

#ifndef MAP_PLATFORMER_PATHFINDING
struct GamePathfindingGridElement
{
  bool m_Passable = true;
};

struct GamePathfindingEvalInfo
{
};

struct GamePathfindingGridEvaluator
{
  GameNetVal operator ()(const GamePathfindingGridElement & a, const GamePathfindingGridElement & b, const GamePathfindingEvalInfo & eval_info) const
  {
    return b.m_Passable ? GameNetVal(1) : GameNetVal(-1);
  }
};

using PathfindingDatabaseType = PathfindingBasicGrid2D<GamePathfindingGridElement, GameNetVal, GamePathfindingGridEvaluator, GamePathfindingEvalInfo, true, true>;
#endif

struct GameCollisionLine
{
  Vector2 m_Start;
  Vector2 m_End;
  int m_Team;
};

class GameStage
{
public:
  GameStage(const Map & map);
  ~GameStage();

  const MapPropertiesDef & GetMapProperties() const;

  const StaticCollisionDatabase & GetCollisionDatabase() const;
  std::vector<Vector2> FindPath(const Vector2 & start, const Vector2 & end, int max_iterations) const;

  const IntersectionDatabase<GameNetVal> & GetIntersectionDatabase() const;
  const std::vector<GameCollisionLine> GetCollisionLines() const;

  const std::vector<std::vector<Vector2>> & GetPlayerSpawns() const;
  const std::vector<Vector2> & GetNPCSpawns() const;
  const std::vector<Vector2> & GetCoverPoints() const;
  const std::vector<Box> & GetKillVolumes() const;

  Optional<ServerEntityHandle> FindStaticObject(uint32_t obj_name_hash) const;

  NullOptPtr<const MapAnchor> ResolveHandle(const MapAnchorHandle & handle) const;
  NullOptPtr<const MapPath> ResolveHandle(const MapPathHandle & handle) const;
  NullOptPtr<const MapVolume> ResolveHandle(const MapVolumeHandle & handle) const;

  std::vector<Vector2> QueryNPCSpawns(const Vector2 & pos, int min_dist, int max_dist) const;
  std::vector<Vector2> QueryCoverPoints(const Vector2 & pos, int min_dist, int max_dist) const;

private:
  friend class GameInstance;
  friend class GameClientInstanceContainer;
  friend class GameInstanceStateGameplay;

  GameFullState CreateDefaultGameState() const;
  void InitAllObjects(GameServerWorld & game_world) const;

protected:

  std::vector<Vector2> QueryPointList(const std::vector<Vector2> & points, const Vector2 & pos, int min_dist, int max_dist) const;

private:

  std::shared_ptr<MapDef> m_Map;

  std::vector<ServerEntityStaticInitData> m_StaticEntities;
  std::vector<ServerEntityStaticInitData> m_DynamicEntities;
  int m_DynamicObjectCount;

  StaticCollisionDatabase m_CollisionDatabase;

#ifndef MAP_PLATFORMER_PATHFINDING
  Optional<PathfindingDatabaseType> m_Pathfinding;
  Box m_PathfindingBounds;
  Vector2 m_PathfindingGridSize;
  Vector2 m_PathfindingElementSize;
#endif

  IntersectionDatabase<GameNetVal> m_IntersectionDatabase;
  std::vector<GameCollisionLine> m_CollisionLines;

  std::vector<std::vector<Vector2>> m_PlayerSpawns;
  std::vector<Vector2> m_NPCSpawns;
  std::vector<Vector2> m_CoverPoints;
  std::vector<Box> m_KillVolumes;

  std::unordered_map<uint32_t, ServerEntityHandle> m_StaticObjLookup;
  std::unordered_map<uint32_t, int> m_ServerEntityHandleLookup;
};
