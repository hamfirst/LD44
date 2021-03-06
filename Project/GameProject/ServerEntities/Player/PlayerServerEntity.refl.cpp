

#include "GameProject/GameCommon.h"

#include "Project/GameServerFramework/GameServerWorld.h"

#include "GameProject/GameServerEventSender.h"
#include "GameProject/GameStage.h"
#include "GameProject/GameCollisionType.refl.h"
#include "GameProject/GameController.refl.h"

#include "GameProject/ServerEntities/Player/PlayerServerEntity.refl.h"
#include "GameProject/ServerEntities/Player/PlayerServerEntity.refl.meta.h"
#include "GameProject/ServerEntities/Player/States/PlayerStateIdle.refl.h"
#include "GameProject/ServerEntities/Player/States/PlayerStateJump.refl.h"
#include "GameProject/ServerEntities/Player/States/PlayerStateBite.refl.h"

#include "GameProject/ServerEntities/Projectile/ProjectileServerEntity.refl.meta.h"
#include "GameProject/ServerEntities/Pickups/HealthPickup/HealthPickup.refl.h"
#include "GameProject/ServerEntities/Bot/NPC/NPCBot.refl.h"
#include "GameProject/ServerEntities/Player/PlayerConfig.refl.meta.h"
#include "GameProject/ServerEntities/Projectile/ProjectileConfig.refl.meta.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/ClientEntity/ClientEntityResource.h"
#include "Runtime/Animation/AnimationState.h"

// Vampire
CLIENT_ASSET(ClientAssetType::kAudio, "./Sounds/PoofFromBat.wav", g_PoofFromBatAudio);
CLIENT_ASSET(ClientAssetType::kAudio, "./Sounds/TransformToBat.wav", g_PoofToBatAudio);

struct PlayerServerEntityConfigResources
{
  ClientEntityResourcePtr m_PlayerEntity;
  ConfigPtr<ProjectileConfig> m_ProjectileConfig;
};

void PlayerServerEntityConfigResourcesLoad(const ConfigPtr<PlayerConfig> & config, PlayerServerEntityConfigResources & resources)
{
  resources.m_PlayerEntity = g_GlobalAssetList.CreateDependentAsset<ClientEntityResource>(config->m_EntityFile.c_str());
  resources.m_ProjectileConfig = g_GlobalAssetList.CreateDependentAsset<GenericResource<ProjectileConfig>>(config->m_ProjectileFile.c_str());
}

GLOBAL_ASSET_ARRAY(ConfigPtr<PlayerConfig>, g_PlayerConfig, "./Gameplay/PlayerConfig.playerconfig");
GLOBAL_DEPENDENT_ASSET_ARRAY(PlayerServerEntityConfigResources, g_PlayerConfigResources, g_PlayerConfig, PlayerServerEntityConfigResourcesLoad);

void PlayerServerEntity::Init(const PlayerServerEntityInitData & init_data, GameServerWorld & game_world)
{
  m_State.SetType<PlayerStateIdle>();
}

void PlayerServerEntity::UpdateFirst(GameServerWorld & game_world)
{
  GameServerEntityBase::UpdateFirst(game_container);
  m_ProcessedAttacks.clear();
}

void PlayerServerEntity::UpdateMiddle(GameServerWorld & game_world)
{
  m_State->PreUpdate(*this, game_container);
  m_State->Move(*this, game_container);

  m_Retransition = true;
  m_State->Transition(*this, game_container);
  m_Retransition = false;

  m_State->Animate(*this, game_container);
  m_State->PostUpdate(*this, game_container);

  // Vampire (just the if)
  if(m_Bat == false && game_container.GetInstanceData().m_RoundState == RoundState::kRound)
  {
    auto move_box = GetMoveBox();

    if(move_box)
    {
      PushCVCBox(move_box.Value(), game_container);
      game_container.GetServerObjectEventSystem().PushEventReceiver<PickupAvailableEvent>(GetEntityHandle(), move_box.Value());
    }

    PushSelfAsTarget(game_container);

    PushReceiveDamageEventBoxes(COMPILE_TIME_CRC32_STR("ReceiveDamage"), game_container);
    PushReceiveDamageCollisionBoxes(COMPILE_TIME_CRC32_STR("ReceiveDamage"), game_container);
  }
}

void PlayerServerEntity::UpdateLast(GameServerWorld & game_world)
{
  auto box = GetSprite()->GetSingleBoxDefault(COMPILE_TIME_CRC32_STR("MoveBox"));
  box = box.Offset(m_Position);

  for (auto & kill_vol : game_container.GetStage().GetKillVolumes())
  {
    if (BoxIntersect(box, kill_vol))
    {
      DamageEvent ev;
      ev.m_Amount = 255;
      ev.m_Direction = m_Facing;
      ev.m_Source = -1;
      ev.m_AttackId = -1;
      ev.m_DamageType = DamageType::kFall;

      SendEvent(ev, EventMetaData(game_container));
      return;
    }
  }

  --m_RefireTime;
  --m_FrozenFrames;

  // Vampire
  if(m_BatTimer > 0)
  {
    --m_BatTimer;

    if(m_BatTimer == 0)
    {
      game_container.GetEventSender().SendVfxSpriteAttachedEvent(GetSlotIndex(),
              GameNetVec2(0, -1), COMPILE_TIME_CRC32_STR("./Sprites/Spells.sprite"), COMPILE_TIME_CRC32_STR("Spell2"));
      game_container.GetEventSender().SendSoundEvent(GetPosition(), g_PoofFromBatAudio, false);
      m_Bat = false;

      m_FrozenFrames = 20;
    }
  }
}

void PlayerServerEntity::ResetState(GameServerWorld & game_world)
{
  TransitionToState<PlayerStateIdle>(game_container);

  if (GetSlotIndex() == 0)
  {
    m_Facing = CharacterFacing::kRight;
  }
  else
  {
    m_Facing = CharacterFacing::kLeft;
  }
}

MoverResult PlayerServerEntity::MoveCheckCollisionDatabase(GameServerWorld & game_world, const GameNetVec2 & extra_movement)
{
#ifdef MOVER_ONE_WAY_COLLISION
  auto result = GameServerEntityBase::MoveCheckCollisionDatabase(game_container, m_Velocity + extra_movement, m_FallThrough);
#else
  auto result = GameServerEntityBase::MoveCheckCollisionDatabase(game_container, m_Velocity + extra_movement);
#endif

  if (result.m_HitRight)
  {
    m_Velocity.x = 0;
  }
  else if (result.m_HitLeft)
  {
    m_Velocity.x = 0;
  }

  if (result.m_HitTop)
  {
    m_Velocity.y = 0;
  }
  else if (result.m_HitBottom)
  {
    m_Velocity.y = 0;
  }

#ifdef PLATFORMER_MOVEMENT

  m_OnGround = result.m_HitBottom;
  m_OnOneWayCollision = result.m_HitBottom && result.m_HitBottom->m_Mask == (uint32_t)GameCollisionType::kCollisionOneWay;

  m_FallThrough = false;

#endif

  return result;
}

#if defined(PLATFORMER_MOVEMENT)
void PlayerServerEntity::Jump(GameServerWorld & game_world)
{
#if defined(PLAYER_ENABLE_JUMP)
  if (m_OnGround)
  {
    if (m_OnOneWayCollision && m_Input.m_YInput < GameNetVal(GetConfig()->m_FallthroughThreshold).Invert())
    {
      m_FallThrough = true;
    }
    else
    {
      game_container.GetEventSender().BroadcastServerAuthEvent(PlaceholderServerAuthEvent{});

      m_Velocity.y += GetConfig()->m_JumpSpeed;
      m_OnGround = false;

      TransitionToState<PlayerStateJump>(game_container);
    }
  }
  else if (m_State.Is<PlayerStateJump>())
  {
    auto jump_state = m_State.Get<PlayerStateJump>();

    if (jump_state->CanGraceJump())
    {
      m_Velocity.y += GetConfig()->m_JumpSpeed;
      TransitionToState<PlayerStateJump>(game_container);
    }
  }

#endif
}
#endif

#ifdef NET_USE_AIM_DIRECTION
void PlayerServerEntity::Fire(GameServerWorld & game_world)
{
  if(m_RefireTime == 0 && m_Bat == false && game_container.GetInstanceData().m_RoundState == RoundState::kRound &&
      m_NPCBeingEaten.GetRawSlotIndex() == -1 && m_Ammo > 0)
  {
    --m_Ammo;

    auto aim_x = GameNetLUT::Cos(m_Input.m_AimDirection);
    auto aim_y = GameNetLUT::Sin(m_Input.m_AimDirection);

    auto aim_dir = GameNetVec2(aim_x, aim_y);
    auto offset = GameNetVec2(aim_x * GameNetVal(5), (aim_y * GameNetVal(3)) - GameNetVal(4));

    auto pos = m_Position;
    pos += offset;

    auto proj = ProjectileServerEntity::SpawnProjectile(pos, aim_dir, GetTeam(game_container), GetEntityHandle(),
            g_PlayerConfigResources[m_Config.CurrentIndex()].m_ProjectileConfig, game_container);

    if(m_Upgrades & (int)PlayerUpgrade::kDamage1)
    {
      proj->m_DamageBoost++;
    }

    if(m_Upgrades & (int)PlayerUpgrade::kDamage2)
    {
      proj->m_DamageBoost++;
    }

    game_container.GetEventSender().SendMuzzleFlashEvent(GetSlotIndex(), m_Input.m_AimDirection);
    m_RefireTime = 20;

    if(m_Upgrades & (int)PlayerUpgrade::kRate1)
    {
      m_RefireTime -= 4;
    }

    if(m_Upgrades & (int)PlayerUpgrade::kRate2)
    {
      m_RefireTime -= 4;
    }

    // Vampire
    //RemoveFromGame(game_container);
  }
}
#endif

void PlayerServerEntity::Use(GameServerWorld & game_world)
{
  //Vampire
  if(m_InCoffin || m_NPCBeingEaten.GetRawSlotIndex() != -1 || game_container.GetInstanceData().m_RoundState != RoundState::kRound)
  {
    return;
  }

  // Look for NPCs to eat or Coffins to use
  auto & obj_manager = game_container.GetObjectManager();
  obj_manager.VisitEntities([&](auto index, NotNullPtr<ServerEntity> object)
  {
    auto npc = object->CastTo<NPCBot>();
    if(npc && npc->m_BeingEaten == false)
    {
      auto dist = ManhattanDist(m_Position, npc->m_Position);
      if(dist > GameNetVal(16))
      {
        return;
      }

      GameNetVal aim_x = GameNetLUT::Cos(m_Input.m_AimDirection);

      npc->m_Position = m_Position;
      if(aim_x > GameNetVal(0))
      {
        npc->m_Position += GameNetVec2(4, 0);
      }
      else
      {
        npc->m_Position -= GameNetVec2(4, 0);
      }

      npc->m_Velocity = GameNetVec2(0, 0);
      npc->m_BeingEaten = true;

      m_NPCBeingEaten = npc->GetEntityHandle();

      TransitionToState<PlayerStateBite>(game_container);
    }
  });
}

void PlayerServerEntity::RemoveFromGame(GameServerWorld & game_world)
{
  Destroy(game_container.GetObjectManager());
}

bool PlayerServerEntity::HandlePlaceholderEvent(const PlaceholderEvent & ev, const EventMetaData & meta)
{
  return true;
}

bool PlayerServerEntity::HandleDamageEvent(const DamageEvent & ev, const EventMetaData & meta)
{
  auto & game = *meta.m_GameLogicContainer;

#ifdef NET_USE_ROUND_TIMER
  if (game.GetInstanceData().m_RoundState != RoundState::kRound)
  {
    return false;
  }
#endif

  if (m_Invulnerable)
  {
    return false;
  }

  if (ev.m_Source == GetSlotIndex())
  {
    return false;
  }

  if (vfind(m_ProcessedAttacks, ev.m_AttackId))
  {
    return false;
  }

  m_ProcessedAttacks.push_back(ev.m_AttackId);

  if (ev.m_Amount >= m_Health)
  {
    // Vampire
    if(m_Lives > 0)
    {
      --m_Lives;
      m_Health = 1;

      PoofToBat(game, true);

      HealthPickupInitData health_pickup_init_data;
      auto health_pickup = game.GetObjectManager().CreateDynamicEntity<HealthPickup>(game, &health_pickup_init_data);
      health_pickup->m_Position = m_Position - GameNetVec2(0, 5);
      health_pickup->m_AvoidObject = GetEntityHandle();
    }
    else
    {
      game.GetEventSender().SendVfxSpriteAttachedEvent(GetSlotIndex(),
              GameNetVec2(0, -1), COMPILE_TIME_CRC32_STR("./Sprites/Spells.sprite"), COMPILE_TIME_CRC32_STR("Spell6"));

      RemoveFromGame(game);
    }
  }
  else
  {
    m_Health -= ev.m_Amount;
  }

  return true;
}

bool PlayerServerEntity::HandleDealDamageEvent(const DealDamageAnimationEvent & ev, const EventMetaData & meta)
{
  auto & game_container = *meta.m_GameLogicContainer;

  for (auto b = meta.m_ActiveAreaStart; b != meta.m_ActiveAreaEnd; ++b)
  {
    DamageEvent dmg;
    dmg.m_Amount = ev.m_Amount;
    dmg.m_DamageType = ev.m_DamageType;
    dmg.m_AttackId = m_AttackId;
    dmg.m_Source = GetSlotIndex();
    dmg.m_Direction = m_Facing.ToEnum();

    PushDealDamageEventBox(*b, dmg, game_container);
  }

  return true;
}

bool PlayerServerEntity::HandlePickupAvailableEvent(const PickupAvailableEvent & ev, const EventMetaData & meta)
{
  if(meta.m_SourceServerObject == nullptr)
  {
    return false;
  }

  auto pickup = meta.m_SourceServerObject->CastTo<PickupBase>();
  if(pickup == nullptr)
  {
    return false;
  }

  if(pickup->CanBePickedUp(this, *meta.m_GameLogicContainer) == false)
  {
    return false;
  }

  pickup->PickUp(this, *meta.m_GameLogicContainer);
  return true;
}

Optional<AnimationState> PlayerServerEntity::GetAnimationState() const
{
  AnimationState state;
  state.m_AnimIndex = m_AnimIndex;
  state.m_AnimFrame = m_AnimFrame;
  state.m_AnimDelay = m_AnimDelay;
  return state;
}

void PlayerServerEntity::SetAnimationState(const AnimationState & anim_state)
{
  m_AnimIndex = anim_state.m_AnimIndex;
  m_AnimFrame = anim_state.m_AnimFrame;
  m_AnimDelay = anim_state.m_AnimDelay;
}

Optional<int> PlayerServerEntity::GetAssociatedPlayer(GameServerWorld & game_world) const
{
  return GetSlotIndex();
}

int PlayerServerEntity::GetTeam(GameServerWorld & game_world) const
{
  return game_container.GetLowFrequencyInstanceData().m_Players[GetSlotIndex()].m_Team;
}

const SpritePtr & PlayerServerEntity::GetSprite() const
{
  return g_PlayerConfigResources[m_Config.CurrentIndex()].m_PlayerEntity->GetSprite();
}

Optional<CharacterFacing> PlayerServerEntity::GetFacing() const
{
  return m_Facing.ToEnum();
}

czstr PlayerServerEntity::GetEntityBinding() const
{
  return GetConfig()->m_EntityFile.c_str();
}

czstr PlayerServerEntity::GetDefaultEntityBinding() const
{
  static PlayerConfig config;
  return config.m_EntityFile.c_str();
}

const ConfigPtr<PlayerConfig> & PlayerServerEntity::GetConfig() const
{
  return m_Config.Value();
}

void PlayerServerEntity::PoofToBat(GameServerWorld & game_world, bool play_audio)
{
  m_Bat = true;
  m_BatTimer = kMaxBatTimer;

  game_container.GetEventSender().SendVfxSpriteAttachedEvent(GetSlotIndex(),
          GameNetVec2(0, -1), COMPILE_TIME_CRC32_STR("./Sprites/Spells.sprite"), COMPILE_TIME_CRC32_STR("Spell3"));

  if(play_audio)
  {
    game_container.GetEventSender().SendSoundEvent(GetPosition(), g_PoofToBatAudio, false);
  }

  m_FrozenFrames = 40;
}

void PlayerServerEntity::GiveHealth(int health)
{
  auto max_health = GetMaxHealth();
  m_Health = std::min(max_health, (int)m_Health + health);
}

void PlayerServerEntity::RefillAmmo()
{
  m_Ammo = kDefaultAmmo;
  if(m_Upgrades & (int)PlayerUpgrade::kAmmo1)
  {
    m_Ammo += 6;
  }

  if(m_Upgrades & (int)PlayerUpgrade::kAmmo2)
  {
    m_Ammo += 6;
  }
}

int PlayerServerEntity::GetMaxHealth()
{
  auto health = kDefaultMaxHealth;

  if(m_Upgrades & (int)PlayerUpgrade::kHealth1)
  {
    health += 2;
  }

  if(m_Upgrades & (int)PlayerUpgrade::kHealth2)
  {
    health += 2;
  }

  return health;
}

int PlayerServerEntity::GetUpgradeCost(PlayerUpgrade upgrade)
{
  if(m_Upgrades & (int)upgrade)
  {
    return 0;
  }

  if(upgrade == PlayerUpgrade::kDamage2 && (m_Upgrades & (int)PlayerUpgrade::kDamage1) == 0)
  {
    return 0;
  }

  if(upgrade == PlayerUpgrade::kAmmo2 && (m_Upgrades & (int)PlayerUpgrade::kAmmo1) == 0)
  {
    return 0;
  }

  if(upgrade == PlayerUpgrade::kHealth2 && (m_Upgrades & (int)PlayerUpgrade::kHealth1) == 0)
  {
    return 0;
  }

  if(upgrade == PlayerUpgrade::kLife2 && (m_Upgrades & (int)PlayerUpgrade::kLife1) == 0)
  {
    return 0;
  }

  if(upgrade == PlayerUpgrade::kLife3 && (((m_Upgrades & (int)PlayerUpgrade::kLife1) == 0) || (m_Upgrades & (int)PlayerUpgrade::kLife2) == 0))
  {
    return 0;
  }

  if(upgrade == PlayerUpgrade::kRate2 && (m_Upgrades & (int)PlayerUpgrade::kRate1) == 0)
  {
    return 0;
  }

  if(((upgrade == PlayerUpgrade::kLife1) || (upgrade == PlayerUpgrade::kLife2) || (upgrade == PlayerUpgrade::kLife3)) && m_Lives >= 3)
  {
    return 0;
  }

  switch(upgrade)
  {
    default:
      return 0;
    case PlayerUpgrade::kDamage1:
      return 3;
    case PlayerUpgrade::kDamage2:
      return 7;
    case PlayerUpgrade::kAmmo1:
      return 2;
    case PlayerUpgrade::kAmmo2:
      return 3;
    case PlayerUpgrade::kHealth1:
      return 3;
    case PlayerUpgrade::kHealth2:
      return 6;
    case PlayerUpgrade::kSpeed1:
      return 6;
    case PlayerUpgrade::kLife1:
      return 4;
    case PlayerUpgrade::kLife2:
      return 5;
    case PlayerUpgrade::kLife3:
      return 6;
    case PlayerUpgrade::kRate1:
      return 5;
    case PlayerUpgrade::kRate2:
      return 7;
  }
}

void PlayerServerEntity::PurchaseUpgrade(PlayerUpgrade upgrade)
{
  auto cost = GetUpgradeCost(upgrade);
  if(cost == 0)
  {
    return;
  }

  m_Upgrades |= (int)upgrade;
  m_Health -= cost;

  if(upgrade == PlayerUpgrade::kLife1 || upgrade == PlayerUpgrade::kLife2 || upgrade == PlayerUpgrade::kLife3)
  {
    ++m_Lives;
  }
}