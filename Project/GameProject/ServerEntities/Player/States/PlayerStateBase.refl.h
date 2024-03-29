#pragma once

#include "StormNet/NetReflectionStruct.h"
#include "StormNet/NetReflectionTypeDatabase.h"

#include "GameProject/GameCommon.h"
#include "GameProject/GameServerTypes.h"
#include "Project/GameServerFramework/GameServerWorld.h"

#include "GameProject/ServerEntities/Player/PlayerConfig.refl.h"

#include "Runtime/Event/EventHandler.h"
#include "Runtime/Config/ConfigResource.h"

#include "StormRefl/StormReflMetaInfoBase.h"


#define DECLARE_PLAYER_STATE \
        NET_REFL; \
        STORM_REFL_FUNCS;

class PlayerServerEntity;

class PlayerStateBase
{
public:
  DECLARE_PLAYER_STATE;
  NET_DECLARE_BASE_TYPE;

  virtual void Init(PlayerServerEntity & player, GameServerWorld & game_world) {};
  virtual void PreUpdate(PlayerServerEntity & player, GameServerWorld & game_world) {};

  virtual void Move(PlayerServerEntity & player, GameServerWorld & game_world) {};
  virtual void Transition(PlayerServerEntity & player, GameServerWorld & game_world) {};
  virtual void Animate(PlayerServerEntity & player, GameServerWorld & game_world) {};

  virtual void PostUpdate(PlayerServerEntity & player, GameServerWorld & game_world) {};

  virtual void Cleanup(PlayerServerEntity & player, GameServerWorld & game_world) {};
  virtual void Destroy(PlayerServerEntity & player, GameServerWorld & game_world) {};

};

template <typename T>
using PlayerStateEventHandler = EventHandler<T>;
