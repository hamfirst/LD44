#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

#include "Runtime/ClientComponent/ClientComponentInitData.refl.h"
#include "Runtime/ClientComponent/ClientComponentInitDataTypeDatabase.h"

struct RUNTIME_EXPORT ClientEntityDef
{
  STORM_DATA_DEFAULT_CONSTRUCTION(ClientEntityDef);

  RString STORM_REFL_ATTR_VAL(file, sprite) m_Sprite;

  RMergeList<RPolymorphic<ClientComponentInitData>> m_Components;
};

