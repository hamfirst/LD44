#pragma once

#include "Game/GameNetworkData.refl.h"
#include "GameShared/GameLogicContainer.h"



class PlayerAI
{
public:
  static void InitAI(GameLogicContainer & game, std::size_t player_index);
  static void UpdateAI(GameLogicContainer & game, std::size_t player_index);

public:

};
