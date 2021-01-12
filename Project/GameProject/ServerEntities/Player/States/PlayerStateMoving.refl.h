#pragma once

#include "GameProject/ServerEntities/Player/States/PlayerStateBase.refl.h"

class PlayerStateMoving : public PlayerStateBase, public PlayerStateEventHandler<PlayerStateMoving>
{
public:
  DECLARE_PLAYER_STATE;

  virtual void Move(PlayerServerEntity & player, GameServerWorld & game_world) override;
  virtual void Transition(PlayerServerEntity & player, GameServerWorld & game_world) override;
  virtual void Animate(PlayerServerEntity & player, GameServerWorld & game_world) override;

public:
};

