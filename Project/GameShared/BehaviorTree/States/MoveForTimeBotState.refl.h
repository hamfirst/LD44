

#pragma once

#include "GameShared/GameSharedCommon.h"
#include "Game/GameFullState.refl.h"

#include "Game/ServerEntities/Bot/BotServerObject.refl.h"


class MoveForTimeBotState
{
public:
  NET_REFL;
  STORM_REFL_NODEFAULT;

  MoveForTimeBotState(const GameNetVec2 vel, uint32_t animation_hash, int frames, bool stop_when_blocked = true);

  void Activate(BotServerObject & bot, GameLogicContainer & container);
  bool Update(BotServerObject & bot, GameLogicContainer & container);

private:
  GameNetVec2 m_Velocity;
  uint32_t m_AnimationHash;
  int m_Frames;
  bool m_StopWhenBlocked;
};

