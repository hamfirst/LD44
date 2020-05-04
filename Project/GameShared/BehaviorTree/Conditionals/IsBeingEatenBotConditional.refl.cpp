#include "Game/GameCommon.h"

#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"

#include "GameShared/GameServerWorld.h"

#include "Project/GameShared/BehaviorTree/Conditionals/IsBeingEatenBotConditional.refl.h"
#include "Project/GameShared/BehaviorTree/Conditionals/IsBeingEatenBotConditional.refl.meta.h"

bool IsBeingEatenBotConditional::Check(const BotServerObject & bot, const GameServerWorld & container)
{
  return bot.m_BeingEaten;
}

