#include "GameProject/GameCommon.h"

#include "StormData/StormData.h"
#include "StormData/StormDataTypeDatabase.h"
#include "StormData/StormDataParent.h"

#include "Runtime/Anchor/AnchorTypeDatabase.h"
#include "Runtime/Anchor/AnchorTypeRegister.h"

#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"

#include "GameProject/Data/CoverPoint.refl.h"
#include "GameProject/Data/CoverPoint.refl.meta.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(CoverPoint);
REGISTER_TYPE(CoverPoint, AnchorDataBase);