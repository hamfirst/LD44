
#pragma once

#include "GameProject/GameCommon.h"
#include "GameProject/GameServerTypes.h"
#include "Project/GameServerFramework/GameServerWorld.h"

#include "GameProject/ServerEntities/GameServerEntityBase.refl.h"
#include "GameProject/ServerEntities/Player/States/PlayerStateBase.refl.h"

#include "GameProject/GameplayEvents/PlaceholderEvent.h"
#include "GameProject/GameplayEvents/PickupEvents.h"
#include "GameProject/Data/DealDamageAnimationEvent.refl.h"

#include "GameProject/ServerEntities/Player/PlayerConfig.refl.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Config/ConfigResource.h"

#include "Runtime/ServerEntity/ServerEntity.h"
#include "Runtime/ServerEntity/ServerEntityInitData.refl.h"
#include "Runtime/ServerEntity/ServerEntityRegistrationMacros.h"

#include "StormNet/NetReflectionPolymorphic.h"
#include "StormNet/NetReflectionArrayList.h"
#include "StormNet/NetReflectionBitBuffer.h"
#include "StormNet/NetReflectionStaticList.h"

// Vampire
static const int kMaxBatTimer = 300;
static const int kDefaultMaxHealth = 6;
static const int kAbsoluteMaxHealth = 12;

static const int kDefaultLives = 3;
static const int kDefaultAmmo = 18;
static const int kMaxLives = 5;

enum STORM_REFL_ENUM class PlayerUpgrade
{
  kDamage1 =   0x0001,
  kDamage2 =   0x0002,
  kAmmo1   =   0x0004,
  kAmmo2   =   0x0008,
  kHealth1 =   0x0010,
  kHealth2 =   0x0020,
  kSpeed1  =   0x0040,
  kLife1   =   0x0080,
  kLife2   =   0x0100,
  kLife3   =   0x0200,
  kRate1   =   0x0400,
  kRate2   =   0x0800,
};


struct PlayerServerEntityInitData : public GameServerEntityBaseInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(PlayerServerEntityInitData);
};

EXTERN_GLOBAL_ASSET_ARRAY(ConfigPtr<PlayerConfig>, g_PlayerConfig);
DECLARE_STATIC_LIST_TYPE(PlayerConfigPtr, g_PlayerConfig);

class PlayerServerEntity : public GameServerEntityBase
{
public:
  DECLARE_SERVER_ENTITY;

  PlayerServerEntity() = default;
  PlayerServerEntity(const PlayerServerEntity & rhs) = default;
  PlayerServerEntity(PlayerServerEntity && rhs) = default;

  PlayerServerEntity & operator = (const PlayerServerEntity & rhs) = default;
  PlayerServerEntity & operator = (PlayerServerEntity && rhs) = default;

  void Init(const PlayerServerEntityInitData & init_data, GameServerWorld & game_world);
  void UpdateFirst(GameServerWorld & game_world);
  void UpdateMiddle(GameServerWorld & game_world);
  void UpdateLast(GameServerWorld & game_world);

  void ResetState(GameServerWorld & game_world);

  MoverResult MoveCheckCollisionDatabase(GameServerWorld & game_world, const GameNetVec2 & extra_movement = {});

#ifdef PLATFORMER_MOVEMENT
  void Jump(GameServerWorld & game_world);
#endif

#ifdef NET_USE_AIM_DIRECTION
  void Fire(GameServerWorld & game_world);
#endif

  void Use(GameServerWorld & game_world);

  void RemoveFromGame(GameServerWorld & game_world);

  bool SERVER_ENTITY_EVENT_HANDLER HandlePlaceholderEvent(const PlaceholderEvent & ev, const EventMetaData & meta);
  bool SERVER_ENTITY_EVENT_HANDLER HandleDamageEvent(const DamageEvent & ev, const EventMetaData & meta);
  bool SERVER_ENTITY_EVENT_HANDLER HandleDealDamageEvent(const DealDamageAnimationEvent & ev, const EventMetaData & meta);
  bool SERVER_ENTITY_EVENT_HANDLER HandlePickupAvailableEvent(const PickupAvailableEvent & ev, const EventMetaData & meta);

  virtual Optional<AnimationState> GetAnimationState() const override;
  virtual void SetAnimationState(const AnimationState & anim_state) override;
  virtual Optional<int> GetAssociatedPlayer(GameServerWorld & game_world) const override;
  virtual int GetTeam(GameServerWorld & game_world) const;

  virtual const SpritePtr & GetSprite() const override;
  virtual Optional<CharacterFacing> GetFacing() const override;

  const ConfigPtr<PlayerConfig> & GetConfig() const;
  virtual czstr GetEntityBinding() const override;
  virtual czstr GetDefaultEntityBinding() const override;

  template <typename State>
  NullOptPtr<State> TransitionToState(GameServerWorld & game_world)
  {
    NetPolymorphic<PlayerStateBase> new_state(NetPolymorphicTypeInit<State>{});
    m_State->Cleanup(*this, game_container);
    new_state->Init(*this, game_container);
    m_State->Destroy(*this, game_container);
    m_State = std::move(new_state);

    if (m_Retransition)
    {
      m_State->Transition(*this, game_container);
    }

    return m_State.Get<State>();
  }

  // Vampire
  void PoofToBat(GameServerWorld & game_world, bool play_audio);
  void GiveHealth(int health);
  void RefillAmmo();
  int GetMaxHealth();
  int GetUpgradeCost(PlayerUpgrade upgrade);
  void PurchaseUpgrade(PlayerUpgrade upgrade);

public:
  GameNetVec2 m_Velocity = {};

#ifdef PLATFORMER_MOVEMENT
  bool m_OnGround = true;

#ifdef MOVER_ONE_WAY_COLLISION
  bool m_FallThrough = false;
  bool m_OnOneWayCollision = false;
#endif
#endif

  NetRangedNumber<int, -1, 30> m_AnimIndex = -1;
  NetRangedNumber<int, 0, 31> m_AnimFrame = 0;
  NetRangedNumber<int, 0, 63> m_AnimDelay = 0;
  NetEnum<CharacterFacing> m_Facing = CharacterFacing::kRight;


  NetRangedNumber<int, 0, 31> m_AttackId = 0;
  bool m_Invulnerable = false;

  NetRangedNumber<int, 0, 20> m_RefireTime = 0;
  NetRangedNumber<int, 0, 30> m_Ammo = kDefaultAmmo;

  ClientInput m_Input;

  NetPolymorphic<PlayerStateBase> m_State;
  PlayerConfigPtr m_Config;

  // VampireShowdown
  bool m_Bat = false;
  NetRangedNumber<int, 0, kMaxBatTimer> m_BatTimer;

  NetRangedNumber<int, 0, kAbsoluteMaxHealth> m_Health = kDefaultMaxHealth;
  NetRangedNumber<int, 0, kMaxLives> m_Lives = kDefaultLives;


  ServerEntityHandle m_NPCBeingEaten;
  bool m_InCoffin = false;


  NetRangedNumber<int, 0, 64> m_FrozenFrames = 0;
  int16_t m_Upgrades;

private:
  bool m_Retransition = false;
  bool m_Destroyed = false;
  std::vector<uint32_t> m_ProcessedAttacks;
};
