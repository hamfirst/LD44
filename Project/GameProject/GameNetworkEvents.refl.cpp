#include "GameProject/GameCommon.h"
#include "StormNet/NetReflectionTypeDatabaseRegister.h"

#include "GameProject/GameNetworkEvents.refl.meta.h"

NET_REGISTER_BASE_TYPE(GlobalNetworkEvent);
NET_REGISTER_BASE_TYPE(ServerAuthNetworkEvent);
NET_REGISTER_BASE_TYPE(TargetNetworkEvent);
NET_REGISTER_BASE_TYPE(ClientNetworkEvent);
NET_REGISTER_ALL_TYPES_FOR_FILE(GameNetworkEvents);
