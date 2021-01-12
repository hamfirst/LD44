
#include "GameProject/GameCommon.h"
#include "GameProject/GameServerEventSender.h"
#include "GameProject/ServerEntities/Projectile/ProjectileServerEntity.refl.h"
#include "GameProject/ServerEntities/Projectile/Response/ProjectileResponseDefault.refl.meta.h"
#include "GameProject/GameplayEvents/DamageType.refl.meta.h"

#include "Runtime/ServerEntity/ServerEntity.h"
#include "Runtime/ServerEntity/ServerEntityHandle.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(ProjectileResponseDefaultConfig);
REGISTER_LOGIC_TYPE(ProjectileResponseDefaultConfig, ProjectileResponseBaseConfig, ProjectileResponseDefault, ProjectileResponseBase);

NET_REGISTER_TYPE(ProjectileResponseDefault, ProjectileResponseBase)

void ProjectileResponseDefault::HandleImpact(NullOptPtr<CollisionDatabaseTraceResult> collision_result,
                                          ProjectileServerEntity & proj, GameServerWorld & game_world)
{
  auto config = GetConfigAs<ProjectileResponseDefaultConfig>();
  if(config == nullptr)
  {
    ASSERT(false, "Could not cast config");
    return;
  }

  auto hit_character_handle = collision_result->m_HitObject.Get<ServerEntityHandle>();
  game_container.GetEventSender().SendProjectileImpactEvent(hit_character_handle != nullptr, collision_result->m_ImpactPos);

  proj.m_Position = collision_result->m_ImpactPos;
  proj.m_Destroyed = true;

  if(hit_character_handle)
  {
    auto hit_character = hit_character_handle->Resolve(game_container.GetObjectManager());
    if(hit_character)
    {
      auto owner = proj.m_Owner.ResolveTo<GameServerEntityBase>(game_container.GetObjectManager());
      auto facing = GetFacingForDirection(proj.m_Direction);

      DamageEvent dmg;
      dmg.m_Amount = config->m_Damage + proj.m_DamageBoost;
      dmg.m_DamageType = config->m_Type;
      dmg.m_Source = owner ? owner->GetSlotIndex() : -1;
      dmg.m_AttackId = GetRandomNumber();
      dmg.m_Direction = facing.IsValid() ? facing.Value() : CharacterFacing::kRight;

      hit_character->SendEvent<DamageEvent>(dmg, EventMetaData(&proj, &game_container));
    }
  }
}

void ProjectileResponseDefault::HandleRangeExpired(ProjectileServerEntity & proj, GameServerWorld & game_world)
{
  proj.Destroy(game_container.GetObjectManager());
}
