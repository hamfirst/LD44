#pragma once

#include "Game/GameCommon.h"

#include "GameShared/GameServerWorld.h"
#include "GameShared/Systems/GameLogicSystems.h"
#include "GameShared/BehaviorTree/BehaviorTree.h"

#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"
#include "Game/ServerEntities/CharacterFacing.refl.h"
#include "Game/ServerEntities/GameServerEntityBase.refl.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/ServerEntity/ServerEntity.h"
#include "Runtime/ServerEntity/ServerEntityInitData.refl.h"
#include "Runtime/ServerEntity/ServerEntityRegistrationMacros.h"

struct BotServerObjectInitData : public GameServerEntityBaseInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(BotServerObjectInitData);
};

class BotServerObject : public GameServerEntityBase
{
public:
  DECLARE_SERVER_ENTITY;

  BotServerObject() = default;
  BotServerObject(const BotServerObject & rhs) = default;
  BotServerObject(BotServerObject && rhs) = default;

  BotServerObject & operator = (const BotServerObject & rhs) = default;
  BotServerObject & operator = (BotServerObject && rhs) = default;

  void Init(const BotServerObjectInitData & init_data, GameServerWorld & game_container);
  void UpdateFirst(GameServerWorld & game_container);
  void UpdateMiddle(GameServerWorld & game_container);

  virtual Optional<AnimationState> GetAnimationState() const override;
  virtual void SetAnimationState(const AnimationState & anim_state) override;

  virtual NullOptPtr<BotBehaviorTree> GetBehaviorTree();
  virtual Optional<CharacterFacing> GetFacing() const override;
  void RetransitionBT();

public:

  GameNetVec2 m_Velocity = {};

#ifdef PLATFORMER_MOVEMENT
  bool m_OnGround = false;
#endif

  NetRangedNumber<int, -1, 30> m_AnimIndex = -1;
  NetRangedNumber<int, 0, 31> m_AnimFrame = 0;
  NetRangedNumber<int, 0, 63> m_AnimDelay = 0;
  NetEnum<CharacterFacing> m_Facing = CharacterFacing::kRight;
  int16_t m_StateTimer = 0;

  // Vampire
  bool m_Dead = false;
  uint8_t m_AlertedFrames = 0;
  bool m_BeingEaten = false;


private:
  bool m_Retransition = false;
};
