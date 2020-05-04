#include "Game/GameCommon.h"

#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"

#include "GameShared/GameServerWorld.h"

#include "Project/GameShared/BehaviorTree/Conditionals/IsAlertedBotConditional.refl.h"
#include "Project/GameShared/BehaviorTree/Conditionals/IsAlertedBotConditional.refl.meta.h"

bool IsAlertedBotConditional::Check(const BotServerObject & bot, const GameServerWorld & container)
{
  return bot.m_AlertedFrames > 0;
}

