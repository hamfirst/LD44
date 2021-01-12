#pragma once

#include "StormNet/NetProtocol.h"
#include "StormNet/NetPipeMessage.h"
#include "StormNet/NetPipeBuffer.h"
#include "StormNet/NetPipeFullState.h"
#include "StormNet/NetPipeVariant.h"
#include "StormNet/NetPipeRaw.h"
#include "StormNet/NetPipeDeltaState.h"
#include "StormNet/NetPipeDeltaStateReliable.h"
#include "StormNet/NetReflection.h"

#include "GameProject/GameFullState.refl.meta.h"
#include "GameProject/GameMessages.refl.meta.h"
#include "GameProject/GameNetworkData.refl.meta.h"
#include "GameProject/GameNetworkEvents.refl.meta.h"

#include "ProjectSettings/ProjectNetworkSettings.h"

using ServerProtocolDef = NetProtocolDefinition<
  NetPipeMessage<ToServerMessage, NetPipeMode::kReliable>,
  NetPipeRaw<NetPipeMode::kUnreliableSequenced>
  >;

using ClientProtocolDef = NetProtocolDefinition<
  NetPipeMessage<FromServerMessage, NetPipeMode::kReliable>,
  NetPipeMessage<GameStateLoading, NetPipeMode::kUnreliableSequenced>,
  NetPipeRaw<NetPipeMode::kUnreliableSequenced>
  >;


using ServerProtocol = NetProtocolInfo<ServerProtocolDef>::template AsymmetricProtocolType<ClientProtocolDef>;
using ClientProtocol = NetProtocolInfo<ClientProtocolDef>::template AsymmetricProtocolType<ServerProtocolDef>;
