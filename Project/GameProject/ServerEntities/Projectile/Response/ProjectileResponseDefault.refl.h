
#pragma once

#include "GameProject/GameCommon.h"
#include "GameProject/ServerEntities/Projectile/Response/ProjectileResponseBase.refl.h"
#include "GameProject/GameplayEvents/DamageType.refl.h"

#include "StormNet/NetReflection.h"

class ProjectileServerEntity;

struct ProjectileResponseDefaultConfig : public ProjectileResponseBaseConfig
{
  RInt m_Damage = 1;
  REnum<DamageType> m_Type = DamageType::kMelee;
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(ProjectileResponseDefaultConfig);
};

class ProjectileResponseDefault : public ProjectileResponseBase
{
public:
  NET_REFL;

  virtual void HandleImpact(NullOptPtr<CollisionDatabaseTraceResult> collision_result,
                            ProjectileServerEntity & proj, GameServerWorld & game_world);
  virtual void HandleRangeExpired(ProjectileServerEntity & proj, GameServerWorld & game_world);
};

