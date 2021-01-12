#pragma once

#include "GameProject/GameCommon.h"
#include "GameProject/GameServerTypes.h"
#include "GameProject/ServerEntities/Projectile/Motion/ProjectileMotionBase.refl.h"
#include "GameProject/ServerEntities/Projectile/Response/ProjectileResponseBase.refl.h"

struct ProjectileConfig
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(ProjectileConfig);

  RString STORM_REFL_ATTR_VAL(file, entity) m_EntityFile = "./Gameplay/DefaultProjectile.entity";

  RUInt m_MaxDistance = 200;
  RPolymorphic<ProjectileMotionBaseConfig, ProjectileMotionBase> m_MotionConfig;
  RPolymorphic<ProjectileResponseBaseConfig, ProjectileResponseBase> m_ResponseConfig;

  RBool m_Unsynced;
};
