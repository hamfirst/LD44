
#include "GameProject/GameCommon.h"
#include "Foundation/SkipField/SkipField.h"

#include "StormRefl/StormReflMetaFuncs.h"
#include "StormRefl/StormReflJsonStd.h"

#include "StormData/StormData.h"
#include "StormData/StormDataJson.h"

#include "Runtime/Config/ConfigRegistrationMacros.h"

#include "GameProject/GameConfig.refl.h"
#include "GameProject/GameConfig.refl.meta.h"

REGISTER_CONFIG_TYPE(GameConfig, "GameProject Config", "gameconfig", "Configs");
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(GameConfig);
