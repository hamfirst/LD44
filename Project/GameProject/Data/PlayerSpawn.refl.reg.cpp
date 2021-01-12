
#include "GameProject/GameCommon.h"
#include "StormData/StormData.h"
#include "StormData/StormDataTypeDatabase.h"
#include "StormData/StormDataParent.h"

#include "Runtime/Anchor/AnchorTypeDatabase.h"
#include "Runtime/Anchor/AnchorTypeRegister.h"

#include "Foundation/TypeDatabase/TypeDatabase.h"

#include "GameProject/Data/PlayerSpawn.refl.h"
#include "GameProject/Data/PlayerSpawn.refl.meta.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(PlayerSpawn);
REGISTER_TYPE(PlayerSpawn, AnchorDataBase);

