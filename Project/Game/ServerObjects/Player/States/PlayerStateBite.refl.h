#pragma once

#include "StormNet/NetReflectionStruct.h"
#include "StormNet/NetReflectionTypeDatabase.h"

#include "Game/ServerObjects/Player/States/PlayerStateBase.refl.h"

class PlayerStateBite : public PlayerStateBase, public PlayerStateEventHandler<PlayerStateBite>
{
public:
  DECLARE_PLAYER_STATE;

  virtual void Move(PlayerServerObject & player, GameLogicContainer & game_container) override;
  virtual void Transition(PlayerServerObject & player, GameLogicContainer & game_container) override;
  virtual void Animate(PlayerServerObject & player, GameLogicContainer & game_container) override;
  virtual void Cleanup(PlayerServerObject & player, GameLogicContainer & game_container) override;

public:
  bool m_Finished = false;
};
