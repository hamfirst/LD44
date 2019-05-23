
#pragma once

#include "Game/GameCommon.h"
#include "Game/ServerEntities/Projectile/Response/ProjectileResponseBase.refl.h"
#include "Game/GameplayEvents/DamageType.refl.h"

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
                            ProjectileServerEntity & proj, GameLogicContainer & game_container);
  virtual void HandleRangeExpired(ProjectileServerEntity & proj, GameLogicContainer & game_container);
};

