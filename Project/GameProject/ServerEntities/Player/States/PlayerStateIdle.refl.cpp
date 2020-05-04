
#include "Game/GameCommon.h"

#include "GameShared/GameServerWorld.h"
#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"

#include "Game/ServerEntities/Player/PlayerServerEntity.refl.h"

#include "Game/ServerEntities/Player/States/PlayerStateIdle.refl.h"
#include "Game/ServerEntities/Player/States/PlayerStateIdle.refl.meta.h"

#include "Game/ServerEntities/Player/States/PlayerStateMoving.refl.h"
#include "Game/ServerEntities/Player/States/PlayerStateJump.refl.h"
#include "Game/ServerEntities/Player/States/PlayerStateBasicAttack.refl.h"

#include "Runtime/ClientEntity/ClientEntityResource.h"

#include "StormNet/NetReflectionTypeDatabase.h"

NET_REGISTER_TYPE(PlayerStateIdle, PlayerStateBase);

void PlayerStateIdle::Move(PlayerServerEntity & player, GameServerWorld & game_container)
{
#ifndef PLATFORMER_MOVEMENT

  player.m_Velocity.x = 0;
  player.m_Velocity.y = 0;

#else

  player.m_Velocity.x = 0;
  player.m_Velocity.y -= player.GetConfig()->m_Gravity;

  player.MoveCheckCollisionDatabase(game_container);

#endif

}

void PlayerStateIdle::Transition(PlayerServerEntity & player, GameServerWorld & game_container)
{
#ifdef NET_USE_ROUND_TIMER
  if (game_container.GetInstanceData().m_RoundState == RoundState::kPreRound)
  {
    return;
  }
#endif

#ifndef PLATFORMER_MOVEMENT

  if (player.m_Input.m_InputStr > GameNetVal(0) && player.m_FrozenFrames == 0)
  {
    player.TransitionToState<PlayerStateMoving>(game_container);
  }

#else

#ifdef PLAYER_ENABLE_JUMP

  if (player.m_OnGround == false)
  {
    auto jump_state = player.TransitionToState<PlayerStateJump>(game_container);
    if (jump_state)
    {
      jump_state->AllowGraceJump();
    }

    return;
  }

#endif

  if (player.m_Input.m_XInput != GameNetVal(0))
  {
    player.TransitionToState<PlayerStateMoving>(game_container);
    return;
  }

#endif
}

void PlayerStateIdle::Animate(PlayerServerEntity & player, GameServerWorld & game_container)
{
  // Vampire
  if(player.m_Bat)
  {
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("Bat"));
    player.TriggerAnimationEvents(game_container, *this);
    return;
  }

#if defined(NET_USE_AIM_DIRECTION)

  GameNetVal aim_x = GameNetLUT::Cos(player.m_Input.m_AimDirection);
  GameNetVal aim_y = GameNetLUT::Sin(player.m_Input.m_AimDirection);

  if(aim_y > GameNetVal(0))
  {
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("IdleUp"));
  }
  else
  {
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("IdleDown"));
  }

#elif defined(PLATFORMER_MOVEMENT)

  player.FrameAdvance(COMPILE_TIME_CRC32_STR("Idle"));

#else
  switch ((CharacterFacing)player.m_Facing)
  {
  case CharacterFacing::kLeft:
  case CharacterFacing::kRight:
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("Side_Idle"));
    break;
  case CharacterFacing::kUp:
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("Up_Idle"));
    break;
  case CharacterFacing::kDown:
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("Down_Idle"));
    break;
  }

#endif

  player.TriggerAnimationEvents(game_container, *this);
}

