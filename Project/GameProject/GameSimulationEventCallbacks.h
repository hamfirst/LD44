#pragma once

#include "Foundation/Common.h"

#include "ProjectSettings/ProjectNetworkSettings.h"

class GameSimulationEventCallbacks
{
public:
  virtual void HandleWinGame(int winning_team) {};
  virtual void HandleNoLongerAcceptingPlayers() {};
};

