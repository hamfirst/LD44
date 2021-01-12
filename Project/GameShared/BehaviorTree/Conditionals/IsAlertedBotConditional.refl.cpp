#include "GameProject/GameCommon.h"

#include "GameProject/GameServerEventSender.h"
#include "GameProject/GameStage.h"

#include "Project/GameServerFramework/GameServerWorld.h"

#include "Project/GameShared/BehaviorTree/Conditionals/IsAlertedBotConditional.refl.h"
#include "Project/GameShared/BehaviorTree/Conditionals/IsAlertedBotConditional.refl.meta.h"

bool IsAlertedBotConditional::Check(const BotServerObject & bot, const GameServerWorld & container)
{
  return bot.m_AlertedFrames > 0;
}

