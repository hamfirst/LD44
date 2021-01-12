

#include "GameProject/GameCommon.h"


#include "Project/GameServerFramework/GameServerWorld.h"
#include "GameProject/GameServerEventSender.h"
#include "GameProject/GameStage.h"

#include "GameProject/ServerEntities/Player/PlayerServerEntity.refl.h"

#include "GameProject/ServerEntities/Player/States/PlayerStateBase.refl.h"
#include "GameProject/ServerEntities/Player/States/PlayerStateBase.refl.meta.h"

#include "GameProject/ServerEntities/Player/States/PlayerStateIdle.refl.h"

#include "StormNet/NetReflectionTypeDatabaseRegister.h"

NET_REGISTER_BASE_TYPE_ABSTRACT(PlayerStateBase);
NET_SET_DEFAULT_TYPE(PlayerStateBase, PlayerStateIdle);

