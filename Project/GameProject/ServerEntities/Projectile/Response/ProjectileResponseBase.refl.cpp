
#include "GameProject/GameCommon.h"
#include "GameProject/ServerEntities/Projectile/ProjectileServerEntity.refl.h"
#include "GameProject/ServerEntities/Projectile/Response/ProjectileResponseBase.refl.meta.h"

#include "Runtime/ServerEntity/ServerEntityComponentSerialize.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(ProjectileResponseBaseConfig);
NET_REGISTER_BASE_TYPE(ProjectileResponseBase);


void ProjectileResponseBase::HandleImpact(NullOptPtr<CollisionDatabaseTraceResult> collision_result,
        ProjectileServerEntity & proj, GameServerWorld & game_world)
{
  proj.m_Position = collision_result->m_ImpactPos;
  proj.m_Destroyed = true;
}

void ProjectileResponseBase::HandleRangeExpired(ProjectileServerEntity & proj, GameServerWorld & game_world)
{
  proj.Destroy(game_container.GetObjectManager());
}
