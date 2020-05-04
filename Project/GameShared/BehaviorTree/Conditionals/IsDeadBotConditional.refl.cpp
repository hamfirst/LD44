
#include "GameShared/BehaviorTree/Conditionals/IsDeadBotConditional.refl.h"

bool IsDeadBotConditional::Check(const BotServerObject & bot, const GameServerWorld & container)
{
  return bot.m_Dead;
}

