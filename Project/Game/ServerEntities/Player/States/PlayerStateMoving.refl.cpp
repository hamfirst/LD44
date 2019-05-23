
#include "Game/GameCommon.h"

#include "GameShared/GameLogicContainer.h"
#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"

#include "Game/ServerEntities/Player/PlayerServerEntity.refl.h"

#include "Game/ServerEntities/Player/States/PlayerStateMoving.refl.h"
#include "Game/ServerEntities/Player/States/PlayerStateMoving.refl.meta.h"

#include "Game/ServerEntities/Player/States/PlayerStateIdle.refl.h"
#include "Game/ServerEntities/Player/States/PlayerStateJump.refl.h"

#include "StormNet/NetReflectionTypeDatabase.h"

NET_REGISTER_TYPE(PlayerStateMoving, PlayerStateBase);

void PlayerStateMoving::Move(PlayerServerEntity & player, GameLogicContainer & game_container)
{
  auto move_speed = (GameNetVal)player.GetConfig()->m_MoveSpeed;

  // Vampire
  if(player.m_Bat)
  {
    move_speed = player.GetConfig()->m_MoveSpeedBat;
  }

#ifndef PLATFORMER_MOVEMENT

  if(player.m_Upgrades & (int)(PlayerUpgrade::kSpeed1))
  {
    move_speed *= GameNetVal("1.25");
  }

  auto move_str = player.m_Input.m_InputStr * move_speed;

  player.m_Velocity.x = GameNetLUT::Cos(player.m_Input.m_InputAngle) * move_str;
  player.m_Velocity.y = GameNetLUT::Sin(player.m_Input.m_InputAngle) * move_str;

  auto result = player.MoveCheckCollisionDatabase(game_container);

#else

  auto target_velocity = player.m_Input.m_XInput * player.GetConfig()->m_MoveSpeed;
  if (player.m_Velocity.x < target_velocity)
  {
    player.m_Velocity.x += player.GetConfig()->m_MoveAccel;
    if (player.m_Velocity.x > target_velocity)
    {
      player.m_Velocity.x = target_velocity;
    }
  }
  else
  {
    player.m_Velocity.x -= player.GetConfig()->m_MoveAccel;
    if (player.m_Velocity.x < target_velocity)
    {
      player.m_Velocity.x = target_velocity;
    }
  }

  player.m_Velocity.y -= player.GetConfig()->m_Gravity;

  player.MoveCheckCollisionDatabase(game_container);

#endif
}

void PlayerStateMoving::Transition(PlayerServerEntity & player, GameLogicContainer & game_container)
{
#ifndef PLATFORMER_MOVEMENT

  if (player.m_Input.m_InputStr == GameNetVal(0) || player.m_FrozenFrames > 0)
  {
    player.TransitionToState<PlayerStateIdle>(game_container);
  }

#else

#ifdef  PLAYER_ENABLE_JUMP

  if (player.m_OnGround == false)
  {
    player.TransitionToState<PlayerStateIdle>(game_container);
    return;
  }

#endif

  if (player.m_Input.m_XInput == GameNetVal(0) && player.m_Velocity.x == GameNetVal(0))
  {
    player.TransitionToState<PlayerStateIdle>(game_container);
    return;
  }

#endif
}


void PlayerStateMoving::Animate(PlayerServerEntity & player, GameLogicContainer & game_container)
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

  int advance = 1;
  if((player.m_Facing == CharacterFacing::kLeft && aim_x < GameNetVal(0)) ||
     (player.m_Facing == CharacterFacing::kRight && aim_x > GameNetVal(0)))
  {
    advance = -1;
  }

  if(aim_y > GameNetVal(0))
  {
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("MoveUp"), true, advance);
  }
  else
  {
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("MoveDown"), true, advance);
  }

#elif deinfed(PLATFORMER_MOVEMENT)

  if (player.m_Input.m_XInput < GameNetVal(0))
  {
    player.m_Facing = CharacterFacing::kLeft;
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("Run"));
  }
  else if(player.m_Input.m_XInput > GameNetVal(0))
  {
    player.m_Facing = CharacterFacing::kRight;
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("Run"));
  }

#else

  auto abs_x = player.m_Velocity.x.Abs();
  auto abs_y = player.m_Velocity.y.Abs();

  if (abs_x < abs_y)
  {
    if (player.m_Velocity.y > GameNetVal(0))
    {
      player.m_Facing = CharacterFacing::kUp;
    }
    else
    {
      player.m_Facing = CharacterFacing::kDown;
    }
  }
  else if (abs_x > abs_y)
  {
    if (player.m_Velocity.x > GameNetVal(0))
    {
      player.m_Facing = CharacterFacing::kRight;
    }
    else
    {
      player.m_Facing = CharacterFacing::kLeft;
    }
  }

  switch ((CharacterFacing)player.m_Facing)
  {
  case CharacterFacing::kLeft:
  case CharacterFacing::kRight:
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("Side_Move"));
    break;
  case CharacterFacing::kUp:
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("Up_Move"));
    break;
  case CharacterFacing::kDown:
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("Down_Move"));
    break;
  }

#endif

  player.TriggerAnimationEvents(game_container, *this);
}
