
#pragma once

#include "Game/GameCommon.h"

#include "Game/GameServerTypes.h"
#include "GameShared/GameServerWorld.h"
#include "Game/GameNetworkData.refl.h"

#include "Game/ServerEntities/CharacterFacing.refl.h"
#include "Game/GameplayEvents/DamageEvent.h"

#include "Runtime/Animation/AnimationState.h"
#include "Runtime/ServerEntity/ServerEntity.h"
#include "Runtime/ServerEntity/ServerEntityInitData.refl.h"
#include "Runtime/ServerEntity/ServerEntityRegistrationMacros.h"

#include "Runtime/Sprite/SpriteResource.h"


struct GameServerEntityBaseInitData : public ServerEntityInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(GameServerEntityBaseInitData);
};

class GameServerEntityBase : public ServerEntity
{
public:
  DECLARE_SERVER_ENTITY;

  GameServerEntityBase() = default;
  GameServerEntityBase(const GameServerEntityBase & rhs) = default;
  GameServerEntityBase(GameServerEntityBase && rhs) = default;

  GameServerEntityBase & operator = (const GameServerEntityBase & rhs) = default;
  GameServerEntityBase & operator = (GameServerEntityBase && rhs) = default;

  void Init(const GameServerEntityBaseInitData & init_data, GameServerWorld & game_container);
  void UpdateFirst(GameServerWorld & container);

  virtual void InitPosition(const Vector2 & pos) override;

  virtual GameNetVec2 GetPosition() const;
  virtual void SetPosition(const GameNetVec2 & pos);

  virtual Optional<AnimationState> GetAnimationState() const;
  virtual void SetAnimationState(const AnimationState & anim_state);
  virtual void SetAssociatedPlayer(int associated_player) const;

  bool FrameAdvance(uint32_t anim_name_hash, bool loop = true, int frames = 1);
  void ResetAnimState();

  Optional<Box> GetMoveBox(uint32_t box_name_hash = COMPILE_TIME_CRC32_STR("MoveBox"));

  void PushDealDamageEventBox(const Box & b, const DamageEvent & damage_event, GameServerWorld & game_container);
  void PushDealDamageEventBox(uint32_t box_name_hash, const DamageEvent & damage_event, GameServerWorld & game_container);
  void PushDealDamageEventBoxes(uint32_t multi_box_name_hash, const DamageEvent & damage_event, GameServerWorld & game_container);
  void PushReceiveDamageEventBox(const Box & b, GameServerWorld & game_container);
  void PushReceiveDamageEventBox(uint32_t box_name_hash, GameServerWorld & game_container);
  void PushReceiveDamageEventBoxes(uint32_t multi_box_name_hash, GameServerWorld & game_container);
  void PushReceiveDamageCollisionBox(const Box & b, GameServerWorld & game_container);
  void PushReceiveDamageCollisionBox(uint32_t box_name_hash, GameServerWorld & game_container);
  void PushReceiveDamageCollisionBoxes(uint32_t multi_box_name_hash, GameServerWorld & game_container);
  void PushCVCBox(const Box & b, GameServerWorld & game_container);
  void PushCVCBox(uint32_t box_name_hash, GameServerWorld & game_container);
  void PushSelfAsTarget(GameServerWorld & game_container);

#if defined(MOVER_ONE_WAY_COLLISION) && PROJECT_PERSPECTIVE == PERSPECTIVE_SIDESCROLLER
  MoverResult MoveCheckCollisionDatabase(GameServerWorld & game_container, const GameNetVec2 & velocity, bool fallthrough = false);
#else
  MoverResult MoveCheckCollisionDatabase(GameServerWorld & game_container, const GameNetVec2 & velocity);
#endif

  GameNetVec2 MoveCheckIntersectionDatabase(GameServerWorld & game_container, const GameNetVec2 & velocity, GameNetVal player_radius, GameNetVal move_threshold);

  std::vector<ServerEntityHandle> QueryTargetDatabase(GameNetVal vision_cone_angle,
          GameNetVal vision_distance, const GameNetVec2 & vision_forward, uint32_t collision_mask,
          GameServerWorld & game_container);

  virtual const SpritePtr & GetSprite() const;
  virtual Optional<CharacterFacing> GetFacing() const;
  virtual Optional<int> GetCollisionId() const;

  template <typename Target>
  void TriggerAnimationEvents(GameServerWorld & game_container, Target & target)
  {
    auto anim_state = GetAnimationState();
    if (anim_state)
    {
      GetSprite()->SendEventsTo(target, anim_state.Value(), EventMetaData(this, &game_container));
    }
  }

private:

  friend class GameServerEntityOverlapSystem;
  Optional<int> m_CollisionId;

public:
  GameNetVec2 m_Position = {};
};
