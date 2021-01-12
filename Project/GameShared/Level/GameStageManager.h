#pragma once

#include "Foundation/Common.h"

#include "Project/GameShared/Level/GameLevelList.h"

#include "GameProject/GameNetworkData.refl.h"
#include "GameProject/GameStage.h"

#include "Runtime/Map/MapResource.h"

class GameStageManager
{
public:

  GameStageManager(GameLevelList & level_list);

  const GameStage * GetStage(const GameInitSettings & settings) const;
  std::size_t GetNumStages() const;

private:
  std::vector<std::unique_ptr<GameStage>> m_Stages;
};

