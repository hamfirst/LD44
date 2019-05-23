#pragma once

#include "Game/ServerEntities/Player/States/PlayerStateBase.refl.h"

class PlayerStateIdle : public PlayerStateBase, public PlayerStateEventHandler<PlayerStateIdle>
{
public:
  DECLARE_PLAYER_STATE;

  virtual void Move(PlayerServerEntity & player, GameLogicContainer & game_container) override;
  virtual void Transition(PlayerServerEntity & player, GameLogicContainer & game_container) override;
  virtual void Animate(PlayerServerEntity & player, GameLogicContainer & game_container) override;

public:
};

