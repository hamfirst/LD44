#include "GameProject/GameCommon.h"

#include "GameProject/GameServerEventSender.h"
#include "GameProject/GameStage.h"

#include "Project/GameServerFramework/GameServerWorld.h"

#include "Project/GameShared/BehaviorTree/States/PlayAnimationForTimeBotState.refl.h"
#include "Project/GameShared/BehaviorTree/States/PlayAnimationForTimeBotState.refl.meta.h"

PlayAnimationForTimeBotState::PlayAnimationForTimeBotState(uint32_t animation_hash, int frames) :
        m_AnimationHash(animation_hash),
        m_Frames(frames)
{

}

void PlayAnimationForTimeBotState::Activate(BotServerObject & bot, GameServerWorld & container)
{
  bot.ResetAnimState();
  bot.m_StateTimer = m_Frames;
}

bool PlayAnimationForTimeBotState::Update(BotServerObject & bot, GameServerWorld & container)
{
  bot.FrameAdvance(m_AnimationHash, true);

  if(bot.m_StateTimer > 0)
  {
    --bot.m_StateTimer;
  }

  return bot.m_StateTimer == 0;
}
