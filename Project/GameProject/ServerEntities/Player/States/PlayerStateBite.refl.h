#pragma once

#include "StormNet/NetReflectionStruct.h"
#include "StormNet/NetReflectionTypeDatabase.h"

#include "GameProject/ServerEntities/Player/States/PlayerStateBase.refl.h"

class PlayerStateBite : public PlayerStateBase, public PlayerStateEventHandler<PlayerStateBite>
{
public:
  DECLARE_PLAYER_STATE;

  virtual void Move(PlayerServerEntity & player, GameServerWorld & game_world) override;
  virtual void Transition(PlayerServerEntity & player, GameServerWorld & game_world) override;
  virtual void Animate(PlayerServerEntity & player, GameServerWorld & game_world) override;
  virtual void Cleanup(PlayerServerEntity & player, GameServerWorld & game_world) override;

public:
  bool m_Finished = false;
};
