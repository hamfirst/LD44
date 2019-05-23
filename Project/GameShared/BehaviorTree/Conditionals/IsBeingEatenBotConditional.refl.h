

#pragma once

#include "GameShared/GameSharedCommon.h"
#include "Game/GameFullState.refl.h"

#include "Game/ServerEntities/Bot/BotServerObject.refl.h"


class IsBeingEatenBotConditional
{
public:
  NET_REFL;
  STORM_REFL_NODEFAULT;

  bool Check(const BotServerObject & bot, const GameLogicContainer & container);

private:
};

