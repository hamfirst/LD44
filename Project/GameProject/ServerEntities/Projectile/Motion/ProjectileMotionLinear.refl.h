
#pragma once

#include "GameProject/ServerEntities/Projectile/Motion/ProjectileMotionBase.refl.h"


struct ProjectileMotionLinearConfig : public ProjectileMotionBaseConfig
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(ProjectileMotionLinearConfig);

  RDeterministicFloat<GameNetVal> m_Speed;
};

class ProjectileMotionLinear : public ProjectileMotionBase
{
public:
  NET_REFL;

  void Init(ProjectileServerEntity & proj, GameServerWorld & game_world) override;
  void Update(ProjectileServerEntity & proj, GameServerWorld & game_world) override;

public:

  GameNetVal m_RangeRemaining;
};
