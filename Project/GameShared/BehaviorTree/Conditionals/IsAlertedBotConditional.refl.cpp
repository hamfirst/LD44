#include "Game/GameCommon.h"

#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"

#include "GameShared/GameLogicContainer.h"

#include "Project/GameShared/BehaviorTree/Conditionals/IsAlertedBotConditional.refl.h"
#include "Project/GameShared/BehaviorTree/Conditionals/IsAlertedBotConditional.refl.meta.h"

bool IsAlertedBotConditional::Check(const BotServerObject & bot, const GameLogicContainer & container)
{
  return bot.m_AlertedFrames > 0;
}

