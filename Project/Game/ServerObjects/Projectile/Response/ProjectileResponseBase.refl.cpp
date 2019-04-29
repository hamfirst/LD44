
#include "Game/GameCommon.h"
#include "Game/ServerObjects/Projectile/ProjectileServerObject.refl.h"
#include "Game/ServerObjects/Projectile/Response/ProjectileResponseBase.refl.meta.h"

#include "Runtime/ServerObject/ServerObjectComponentSerialize.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(ProjectileResponseBaseConfig);
NET_REGISTER_BASE_TYPE(ProjectileResponseBase);


void ProjectileResponseBase::HandleImpact(NullOptPtr<CollisionDatabaseTraceResult> collision_result,
        ProjectileServerObject & proj, GameLogicContainer & game_container)
{
  proj.m_Position = collision_result->m_ImpactPos;
  proj.m_Destroyed = true;
}

void ProjectileResponseBase::HandleRangeExpired(ProjectileServerObject & proj, GameLogicContainer & game_container)
{
  proj.Destroy(game_container.GetObjectManager());
}
