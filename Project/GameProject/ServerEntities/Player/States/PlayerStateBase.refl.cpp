

#include "Game/GameCommon.h"


#include "GameShared/GameServerWorld.h"
#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"

#include "Game/ServerEntities/Player/PlayerServerEntity.refl.h"

#include "Game/ServerEntities/Player/States/PlayerStateBase.refl.h"
#include "Game/ServerEntities/Player/States/PlayerStateBase.refl.meta.h"

#include "Game/ServerEntities/Player/States/PlayerStateIdle.refl.h"

#include "StormNet/NetReflectionTypeDatabaseRegister.h"

NET_REGISTER_BASE_TYPE_ABSTRACT(PlayerStateBase);
NET_SET_DEFAULT_TYPE(PlayerStateBase, PlayerStateIdle);

