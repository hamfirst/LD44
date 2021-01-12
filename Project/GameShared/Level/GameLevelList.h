#pragma once

#include "Foundation/Common.h"

#include "GameLevelListAsset.refl.h"

#include "GameProject/GameNetworkData.refl.h"
#include "GameProject/GameStage.h"

#include "Runtime/Map/MapResource.h"
#include "Runtime/GenericResource/GenericResource.h"

using LevelListPtr = GenericResourcePtr<GameLevelListAsset>;

class GameLevelList
{
public:

  GameLevelList();
  bool IsLevelListLoaded() const;

  void PreloadAllLevels();
  bool IsPreloadComplete();

  Map LoadLevel(std::size_t stage_index);
  const MapDef & GetPreloadedMap(std::size_t stage_index) const;
  const MapPropertiesDef & GetPreloadedMapProperties(std::size_t stage_index) const;

  const LevelListPtr & GetLevelListAsset() const;
  std::size_t GetNumLevels();

private:

  LevelListPtr m_LevelListResource;
  std::vector<Map> m_PreloadedMaps;
};

