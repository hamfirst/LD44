
#pragma once

#include "GameShared/GameSharedCommon.h"
#include "Game/GameFullState.refl.h"

#include "Game/ServerEntities/Bot/BotServerObject.refl.h"


class PlayAnimationBotState
{
public:
  NET_REFL;
  STORM_REFL_NODEFAULT;

  explicit PlayAnimationBotState(uint32_t animation_hash);

  void Activate(BotServerObject & bot, GameServerWorld & container);
  bool Update(BotServerObject & bot, GameServerWorld & container);

private:
  uint32_t m_AnimationHash;
};

