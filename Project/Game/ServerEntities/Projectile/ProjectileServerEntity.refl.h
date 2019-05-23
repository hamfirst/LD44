#pragma once

#include "Game/GameCommon.h"

#include "GameShared/GameLogicContainer.h"
#include "GameShared/Systems/GameLogicSystems.h"

#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"
#include "Game/ServerEntities/GameServerEntityBase.refl.h"
#include "Game/ServerEntities/Projectile/ProjectileConfig.refl.h"
#include "Game/ServerEntities/Projectile/Motion/ProjectileMotionBase.refl.h"

#include "Runtime/Asset/Asset.h"
#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Config/ConfigResource.h"

#include "Runtime/ServerEntity/ServerEntity.h"
#include "Runtime/ServerEntity/ServerEntityInitData.refl.h"
#include "Runtime/ServerEntity/ServerEntityRegistrationMacros.h"
#include "Runtime/ServerEntity/ServerEntityComponent.h"

EXTERN_GLOBAL_ASSET_ARRAY(ConfigPtr<ProjectileConfig>, g_ProjectileConfigs);
DECLARE_STATIC_LIST_TYPE(ProjectileConfigPtr, g_ProjectileConfigs);

struct ProjectileServerEntitySpawnData
{
  STORM_REFL;

  GameNetVec2 m_Position;
  GameNetVec2 m_Direction;
  int m_TeamIndex;
  ServerEntityHandle m_OwnerHandle;
  const ConfigPtr<ProjectileConfig> * m_Config;
};

struct ProjectileServerEntityInitData : public GameServerEntityBaseInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(ProjectileServerEntityInitData);
  ProjectileServerEntitySpawnData STORM_REFL_IGNORE m_SpawnData;
};

class ProjectileServerEntity : public GameServerEntityBase
{
public:
  DECLARE_SERVER_ENTITY;

  ProjectileServerEntity() = default;
  ProjectileServerEntity(const ProjectileServerEntity & rhs) = default;
  ProjectileServerEntity(ProjectileServerEntity && rhs) = default;

  ProjectileServerEntity & operator = (const ProjectileServerEntity & rhs) = default;
  ProjectileServerEntity & operator = (ProjectileServerEntity && rhs) = default;

  void Init(const ProjectileServerEntityInitData & init_data, GameLogicContainer & game_container);
  void UpdateFirst(GameLogicContainer & game_container);
  void UpdateLast(GameLogicContainer & game_container);

  void HandleImpact(NullOptPtr<CollisionDatabaseTraceResult> collision_result, GameLogicContainer & game_container);
  void HandleRangeExpired(GameLogicContainer & game_container);

  static NotNullPtr<ProjectileServerEntity> SpawnProjectile(const GameNetVec2 & pos, const GameNetVec2 & dir,
          int team_index, const ServerEntityHandle & handle,
          const ConfigPtr<ProjectileConfig> & config, GameLogicContainer & game_container);

  virtual czstr GetEntityBinding() const override;
  virtual czstr GetDefaultEntityBinding() const override;
  virtual Optional<int> GetAssociatedPlayer(GameLogicContainer & game_container) const override;
  virtual void InitStaticComponents() override;

public:

  GameNetVec2 m_Direction = {};
  NetRangedNumber<int, -1, kMaxTeams - 1> m_Team;
  ServerEntityHandle m_Owner;
  ProjectileConfigPtr m_Config;
  bool m_Destroyed = false;

  // Vampire
  int8_t m_DamageBoost = 0;

  ServerEntityComponent<ProjectileMotionBase, ProjectileMotionBaseConfig> m_Motion;
  ServerEntityComponent<ProjectileResponseBase, ProjectileResponseBaseConfig> m_Response;
};
