

#pragma once

#include "GameShared/GameSharedCommon.h"
#include "GameProject/GameFullState.refl.h"

#include "GameProject/ServerEntities/Bot/BotServerObject.refl.h"


class IsBeingEatenBotConditional
{
public:
  NET_REFL;
  STORM_REFL_NODEFAULT;

  bool Check(const BotServerObject & bot, const GameServerWorld & container);

private:
};

