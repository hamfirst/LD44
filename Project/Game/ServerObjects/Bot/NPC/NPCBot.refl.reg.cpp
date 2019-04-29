#include "Game/GameCommon.h"
#include "Foundation/SkipField/SkipField.h"

#include "StormRefl/StormReflMetaFuncs.h"
#include "StormRefl/StormReflJsonStd.h"

#include "StormData/StormData.h"
#include "StormData/StormDataJson.h"

#include "Runtime/ServerObject/ServerTypesJson.h"
#include "Runtime/ServerObject/ServerTypesNet.h"
#include "Runtime/ServerObject/ServerObjectRegistrationMacros.h"
#include "Runtime/ServerObject/ServerObjectEventRegister.h"
#include "Runtime/ServerObject/ServerObjectMetaFuncs.h"
#include "Runtime/ServerObject/ServerObjectSystem.h"
#include "Runtime/ServerObject/ServerObjectUpdate.h"
#include "Runtime/ServerObject/ServerObjectSerialize.h"

#include "GameShared/BehaviorTree/BehaviorTreeSerialize.h"

#include "Project/Game/ServerObjects/Bot/NPC/NPCBot.refl.h"
#include "Project/Game/ServerObjects/Bot/NPC/NPCBot.refl.meta.h"

REGISTER_SERVER_OBJECT_WITH_INIT_DATA(NPCBot, NPCBotInitData, BotServerObject);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(NPCBotInitData);
