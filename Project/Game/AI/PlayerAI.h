#pragma once

#include "Game/GameNetworkData.refl.h"
#include "GameShared/GameServerWorld.h"



class PlayerAI
{
public:
  static void InitAI(GameServerWorld & game, std::size_t player_index);
  static void UpdateAI(GameServerWorld & game, std::size_t player_index);

public:

};
