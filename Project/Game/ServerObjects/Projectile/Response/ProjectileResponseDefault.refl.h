
#pragma once

#include "Game/GameCommon.h"
#include "Game/ServerObjects/Projectile/Response/ProjectileResponseBase.refl.h"
#include "Game/GameplayEvents/DamageType.refl.h"

#include "StormNet/NetReflection.h"

class ProjectileServerObject;

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
                            ProjectileServerObject & proj, GameLogicContainer & game_container);
  virtual void HandleRangeExpired(ProjectileServerObject & proj, GameLogicContainer & game_container);
};

