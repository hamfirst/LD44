#include "Game/GameCommon.h"

#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"

#include "GameShared/GameLogicContainer.h"

#include "Project/GameShared/BehaviorTree/Conditionals/IsBeingEatenBotConditional.refl.h"
#include "Project/GameShared/BehaviorTree/Conditionals/IsBeingEatenBotConditional.refl.meta.h"

bool IsBeingEatenBotConditional::Check(const BotServerObject & bot, const GameLogicContainer & container)
{
  return bot.m_BeingEaten;
}

