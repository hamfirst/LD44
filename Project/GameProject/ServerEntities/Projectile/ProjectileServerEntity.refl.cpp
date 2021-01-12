
#include "GameProject/GameCommon.h"

#include "GameProject/GameController.refl.h"
#include "GameProject/GameServerEventSender.h"

#include "GameProject/ServerEntities/Projectile/ProjectileServerEntity.refl.h"
#include "GameProject/ServerEntities/Projectile/ProjectileServerEntity.refl.meta.h"

#include "Runtime/ClientEntity/ClientEntityResource.h"
#include "Runtime/Sprite/SpriteResource.h"

struct ProjectileServerEntityConfigResources
{
  ClientEntityResourcePtr m_ProjectileEntity;
};

void ProjectileConfigResourcesLoad(const ConfigPtr<ProjectileConfig> & config, ProjectileServerEntityConfigResources & resources)
{
  ServerEntityComponent<ProjectileMotionBase, ProjectileMotionBaseConfig>::RegisterConfigType(
          config.GetResource()->GetFileName(), config->m_MotionConfig);
  ServerEntityComponent<ProjectileResponseBase, ProjectileResponseBaseConfig>::RegisterConfigType(
          config.GetResource()->GetFileName(), config->m_ResponseConfig);

  resources.m_ProjectileEntity = g_GlobalAssetList.CreateDependentAsset<ClientEntityResource>(config->m_EntityFile.c_str());
}

GLOBAL_ASSET_DIRECTORY(ConfigPtr<ProjectileConfig>, g_ProjectileConfigs, "./Gaameplay", "projectileconfig");
GLOBAL_DEPENDENT_ASSET_ARRAY(ProjectileServerEntityConfigResources, g_ProjectileConfigInfo, g_ProjectileConfigs, ProjectileConfigResourcesLoad);

void ProjectileServerEntity::Init(const ProjectileServerEntityInitData & init_data, GameServerWorld & game_world)
{
  m_Position = init_data.m_SpawnData.m_Position;
  m_Direction = init_data.m_SpawnData.m_Direction;
  m_Team = init_data.m_SpawnData.m_TeamIndex;
  m_Owner = init_data.m_SpawnData.m_OwnerHandle;

  m_Config.SetTo(*init_data.m_SpawnData.m_Config);
}

void ProjectileServerEntity::UpdateFirst(GameServerWorld & game_world)
{
  if(m_Destroyed)
  {
    Destroy(game_container.GetObjectManager());
    return;
  }

  GameServerEntityBase::UpdateFirst(game_container);
}

void ProjectileServerEntity::UpdateLast(GameServerWorld & game_world)
{
  if(m_Motion)
  {
    m_Motion->Update(*this, game_container);
  }
}

void ProjectileServerEntity::HandleImpact(NullOptPtr<CollisionDatabaseTraceResult> collision_result, GameServerWorld & game_world)
{
  if(m_Response)
  {
    m_Response->HandleImpact(collision_result, *this, game_container);
  }
  else
  {
    m_Destroyed = true;
  }
}

void ProjectileServerEntity::HandleRangeExpired(GameServerWorld & game_world)
{
  if(m_Response)
  {
    m_Response->HandleRangeExpired(*this, game_container);
  }
  else
  {
    Destroy(game_container.GetObjectManager());
  }
}

NotNullPtr<ProjectileServerEntity> ProjectileServerEntity::SpawnProjectile(const GameNetVec2 & pos,
        const GameNetVec2 & dir, int team_index, const ServerEntityHandle & owner_handle,
        const ConfigPtr<ProjectileConfig> & config, GameServerWorld & game_world)
{
  ProjectileServerEntityInitData init_data;
  init_data.m_SpawnData.m_Position = pos;
  init_data.m_SpawnData.m_Direction = dir;
  init_data.m_SpawnData.m_TeamIndex = team_index;
  init_data.m_SpawnData.m_OwnerHandle = owner_handle;
  init_data.m_SpawnData.m_Config = &config;

  NotNullPtr<ProjectileServerEntity> ptr;
  if(config->m_Unsynced)
  {
    ptr = game_container.GetObjectManager().CreateUnsyncedDynamicEntity<ProjectileServerEntity>(game_container, &init_data);
  }
  else
  {
    ptr = game_container.GetObjectManager().CreateDynamicEntity<ProjectileServerEntity>(game_container, &init_data);
  }

  if(ptr->m_Motion)
  {
    ptr->m_Motion->Init(*ptr, game_container);
  }

  return ptr;
}

czstr ProjectileServerEntity::GetEntityBinding() const
{
  return m_Config->m_EntityFile.c_str();
}

czstr ProjectileServerEntity::GetDefaultEntityBinding() const
{
  static ProjectileConfig config;
  return config.m_EntityFile.c_str();
}

Optional<int> ProjectileServerEntity::GetAssociatedPlayer(GameServerWorld & game_world) const
{
  auto owner = m_Owner.Resolve(game_container.GetObjectManager());
  if(owner)
  {
    return owner->GetSlotIndex();
  }

  return {};
}

void ProjectileServerEntity::InitStaticComponents()
{
  m_Motion.SetFromConfig(m_Config->m_MotionConfig.GetValue());
  m_Response.SetFromConfig(m_Config->m_ResponseConfig.GetValue());
}
