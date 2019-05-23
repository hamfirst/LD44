
#pragma once

#include "Game/GameCommon.h"
#include "Game/GameServerTypes.h"
#include "GameShared/GameLogicContainer.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Config/ConfigResource.h"
#include "Runtime/ServerEntity/ServerEntityComponent.h"

#include "StormNet/NetReflection.h"

class ProjectileServerEntity;

struct ProjectileResponseBaseConfig
{
  STORM_DATA_DEFAULT_CONSTRUCTION(ProjectileResponseBaseConfig);
};

class ProjectileResponseBase : public ServerEntityComponentBase<ProjectileResponseBaseConfig>
{
public:
  NET_DECLARE_BASE_TYPE;
  NET_REFL;

  virtual void HandleImpact(NullOptPtr<CollisionDatabaseTraceResult> collision_result,
                            ProjectileServerEntity & proj, GameLogicContainer & game_container);
  virtual void HandleRangeExpired(ProjectileServerEntity & proj, GameLogicContainer & game_container);
};


