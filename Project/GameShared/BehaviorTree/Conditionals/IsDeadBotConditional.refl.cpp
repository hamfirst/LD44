
#include "GameShared/BehaviorTree/Conditionals/IsDeadBotConditional.refl.h"

bool IsDeadBotConditional::Check(const BotServerObject & bot, const GameLogicContainer & container)
{
  return bot.m_Dead;
}

