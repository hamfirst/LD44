#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

#include "Runtime/ServerEntity/ServerEntityInitData.refl.h"
#include "Runtime/ServerEntity/ServerEntityInitDataTypeDatabase.h"

using ServerEntityInitDataPolyType = RPolymorphic<ServerEntityInitData>;

struct RUNTIME_EXPORT ServerEntityDef
{
  STORM_DATA_DEFAULT_CONSTRUCTION(ServerEntityDef);
  RBool m_IsStatic;
  RPolymorphic<ServerEntityInitData> m_InitData;
};

