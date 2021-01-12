
#pragma once

#include "GameProject/GameCommon.h"
#include "GameProject/GameServerTypes.h"
#include "Project/GameServerFramework/GameServerWorld.h"

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
                            ProjectileServerEntity & proj, GameServerWorld & game_world);
  virtual void HandleRangeExpired(ProjectileServerEntity & proj, GameServerWorld & game_world);
};


