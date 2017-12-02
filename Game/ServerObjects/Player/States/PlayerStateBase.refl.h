#pragma once

#include "StormNet/NetReflectionStruct.h"
#include "StormNet/NetReflectionTypeDatabase.h"

#include "Game/GameCommon.h"
#include "Game/GameServerTypes.h"
#include "Game/GameLogicContainer.h"

#include "Runtime/Event/EventHandler.h"

#include "StormRefl/StormReflMetaInfoBase.h"

class PlayerServerObject;

class PlayerStateBase
{
public:
  NET_REFL;
  NET_DECLARE_BASE_TYPE;

  virtual void Init(PlayerServerObject & player, GameLogicContainer & game_container) {};
  virtual void PreUpdate(PlayerServerObject & player, GameLogicContainer & game_container) {};

  virtual void Move(PlayerServerObject & player, GameLogicContainer & game_container) {};
  virtual void Transition(PlayerServerObject & player, GameLogicContainer & game_container) {};
  virtual void Animate(PlayerServerObject & player, GameLogicContainer & game_container) {};

  virtual void PostUpdate(PlayerServerObject & player, GameLogicContainer & game_container) {};

  virtual void Deinit(PlayerServerObject & player, GameLogicContainer & game_container) {};

};

template <typename T>
using PlayerStateEventHandler = EventHandler<T, GameLogicContainer &, const Box *, const Box *>;