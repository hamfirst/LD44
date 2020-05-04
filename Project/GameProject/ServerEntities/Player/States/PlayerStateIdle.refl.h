#pragma once

#include "Game/ServerEntities/Player/States/PlayerStateBase.refl.h"

class PlayerStateIdle : public PlayerStateBase, public PlayerStateEventHandler<PlayerStateIdle>
{
public:
  DECLARE_PLAYER_STATE;

  virtual void Move(PlayerServerEntity & player, GameServerWorld & game_container) override;
  virtual void Transition(PlayerServerEntity & player, GameServerWorld & game_container) override;
  virtual void Animate(PlayerServerEntity & player, GameServerWorld & game_container) override;

public:
};

