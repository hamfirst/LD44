#include "GameProject/GameCommon.h"

#include "GameProject/GameServerEventSender.h"
#include "GameProject/GameStage.h"

#include "Project/GameServerFramework/GameServerWorld.h"

#include "Project/GameShared/BehaviorTree/Conditionals/IsBeingEatenBotConditional.refl.h"
#include "Project/GameShared/BehaviorTree/Conditionals/IsBeingEatenBotConditional.refl.meta.h"

bool IsBeingEatenBotConditional::Check(const BotServerObject & bot, const GameServerWorld & container)
{
  return bot.m_BeingEaten;
}

