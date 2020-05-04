
#include "Game/GameCommon.h"
#include "Game/ServerEntities/Projectile/Motion/ProjectileMotionBase.refl.meta.h"

#include "Runtime/ServerEntity/ServerEntityComponentSerialize.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(ProjectileMotionBaseConfig);
NET_REGISTER_BASE_TYPE(ProjectileMotionBase);


void ProjectileMotionBase::Init(ProjectileServerEntity & proj, GameServerWorld & game_container)
{

}

void ProjectileMotionBase::Update(ProjectileServerEntity & proj, GameServerWorld & game_container)
{

}


