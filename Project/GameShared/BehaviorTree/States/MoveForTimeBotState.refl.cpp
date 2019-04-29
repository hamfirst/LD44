#include "Game/GameCommon.h"

#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"

#include "GameShared/GameLogicContainer.h"

#include "Project/GameShared/BehaviorTree/States/MoveForTimeBotState.refl.h"
#include "Project/GameShared/BehaviorTree/States/MoveForTimeBotState.refl.meta.h"

MoveForTimeBotState::MoveForTimeBotState(const GameNetVec2 vel, uint32_t animation_hash, int frames, bool stop_when_blocked) :
        m_Velocity(vel),
        m_AnimationHash(animation_hash),
        m_Frames(frames),
        m_StopWhenBlocked(stop_when_blocked)
{

}

void MoveForTimeBotState::Activate(BotServerObject & bot, GameLogicContainer & container)
{
  bot.ResetAnimState();
  bot.m_StateTimer = m_Frames;
}

bool MoveForTimeBotState::Update(BotServerObject & bot, GameLogicContainer & container)
{
  bot.FrameAdvance(m_AnimationHash, true);
  bot.m_Velocity = m_Velocity;

  auto facing = GetFacingForDirection(bot.m_Velocity);
  bot.m_Facing = facing ? facing.Value() : (CharacterFacing)bot.m_Facing;

  auto result = bot.MoveCheckCollisionDatabase(container, bot.m_Velocity);
  if(result.m_HitCombined != 0 && m_StopWhenBlocked)
  {
    return true;
  }

  if(bot.m_StateTimer > 0)
  {
    --bot.m_StateTimer;
  }

  return bot.m_StateTimer == 0;
}
