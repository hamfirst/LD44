#include "Game/GameCommon.h"
#include "Foundation/SkipField/SkipField.h"

#include "StormRefl/StormReflMetaFuncs.h"
#include "StormRefl/StormReflJsonStd.h"

#include "StormData/StormData.h"
#include "StormData/StormDataJson.h"

#include "Runtime/ServerEntity/ServerTypesJson.h"
#include "Runtime/ServerEntity/ServerTypesNet.h"
#include "Runtime/ServerEntity/ServerEntityRegistrationMacros.h"
#include "Runtime/ServerEntity/ServerEntityEventRegister.h"
#include "Runtime/ServerEntity/ServerEntityMetaFuncs.h"
#include "Runtime/ServerEntity/ServerEntitySystem.h"
#include "Runtime/ServerEntity/ServerObjectUpdate.h"
#include "Runtime/ServerEntity/ServerEntitySerialize.h"

#include "GameShared/BehaviorTree/BehaviorTreeSerialize.h"

#include "Game/ServerEntities/Bot/NPC/NPCBot.refl.h"
#include "Game/ServerEntities/Bot/NPC/NPCBot.refl.meta.h"

REGISTER_SERVER_ENTITY_WITH_INIT_DATA(NPCBot, NPCBotInitData, BotServerObject);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(NPCBotInitData);
