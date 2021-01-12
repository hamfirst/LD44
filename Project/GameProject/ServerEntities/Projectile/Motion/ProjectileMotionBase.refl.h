
#pragma once

#include "GameProject/GameCommon.h"
#include "GameProject/GameServerTypes.h"
#include "Project/GameServerFramework/GameServerWorld.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Config/ConfigResource.h"
#include "Runtime/ServerEntity/ServerEntityComponent.h"

#include "StormNet/NetReflection.h"

class ProjectileServerEntity;

struct ProjectileMotionBaseConfig
{
  STORM_DATA_DEFAULT_CONSTRUCTION(ProjectileMotionBaseConfig);
};

class ProjectileMotionBase : public ServerEntityComponentBase<ProjectileMotionBaseConfig>
{
public:
  NET_DECLARE_BASE_TYPE;
  NET_REFL;

  virtual void Init(ProjectileServerEntity & proj, GameServerWorld & game_world);
  virtual void Update(ProjectileServerEntity & proj, GameServerWorld & game_world);

};


