

#pragma once

#include "GameShared/GameSharedCommon.h"
#include "GameProject/GameFullState.refl.h"

#include "GameProject/ServerEntities/Bot/BotServerObject.refl.h"


class PlayAnimationForTimeBotState
{
public:
  NET_REFL;
  STORM_REFL_NODEFAULT;

  PlayAnimationForTimeBotState(uint32_t animation_hash, int frames);

  void Activate(BotServerObject & bot, GameServerWorld & container);

  bool Update(BotServerObject & bot, GameServerWorld & container);

private:
  uint32_t m_AnimationHash;
  int m_Frames;
};

