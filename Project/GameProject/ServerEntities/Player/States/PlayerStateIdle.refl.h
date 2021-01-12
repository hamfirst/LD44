#pragma once

#include "GameProject/ServerEntities/Player/States/PlayerStateBase.refl.h"

class PlayerStateIdle : public PlayerStateBase, public PlayerStateEventHandler<PlayerStateIdle>
{
public:
  DECLARE_PLAYER_STATE;

  virtual void Move(PlayerServerEntity & player, GameServerWorld & game_world) override;
  virtual void Transition(PlayerServerEntity & player, GameServerWorld & game_world) override;
  virtual void Animate(PlayerServerEntity & player, GameServerWorld & game_world) override;

public:
};

