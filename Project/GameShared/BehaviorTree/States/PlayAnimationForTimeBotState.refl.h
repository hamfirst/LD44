

#pragma once

#include "GameShared/GameSharedCommon.h"
#include "Game/GameFullState.refl.h"

#include "Game/ServerEntities/Bot/BotServerObject.refl.h"


class PlayAnimationForTimeBotState
{
public:
  NET_REFL;
  STORM_REFL_NODEFAULT;

  PlayAnimationForTimeBotState(uint32_t animation_hash, int frames);

  void Activate(BotServerObject & bot, GameLogicContainer & container);

  bool Update(BotServerObject & bot, GameLogicContainer & container);

private:
  uint32_t m_AnimationHash;
  int m_Frames;
};

