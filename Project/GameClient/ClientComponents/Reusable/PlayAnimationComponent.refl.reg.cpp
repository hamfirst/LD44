
#include "GameClient/GameClientCommon.h"

#include "Engine/ClientComponent/ClientComponentSystem.h"
#include "Engine/ClientComponent/ClientComponentList.h"
#include "Engine/ClientComponent/ClientComponentUpdateRegistrationTemplates.h"
#include "Runtime/ClientComponent/ClientComponentInitDataTypeDatabase.h"
#include "Runtime/ClientComponent/ClientComponentInitDataTypeDatabaseRegister.h"

#include "StormData/StormData.h"
#include "StormData/StormDataJson.h"

#include "GameClient/ClientComponents/Reusable/PlayAnimationComponent.refl.h"
#include "GameClient/ClientComponents/Reusable/PlayAnimationComponent.refl.meta.h"

REGISTER_CLIENT_COMPONENT_WITH_INIT_DATA(PlayAnimationComponent, PlayAnimationComponentInitData, ClientComponent);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(PlayAnimationComponentInitData);
