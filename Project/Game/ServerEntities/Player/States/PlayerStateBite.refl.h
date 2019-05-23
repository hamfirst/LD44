#pragma once

#include "StormNet/NetReflectionStruct.h"
#include "StormNet/NetReflectionTypeDatabase.h"

#include "Game/ServerEntities/Player/States/PlayerStateBase.refl.h"

class PlayerStateBite : public PlayerStateBase, public PlayerStateEventHandler<PlayerStateBite>
{
public:
  DECLARE_PLAYER_STATE;

  virtual void Move(PlayerServerEntity & player, GameLogicContainer & game_container) override;
  virtual void Transition(PlayerServerEntity & player, GameLogicContainer & game_container) override;
  virtual void Animate(PlayerServerEntity & player, GameLogicContainer & game_container) override;
  virtual void Cleanup(PlayerServerEntity & player, GameLogicContainer & game_container) override;

public:
  bool m_Finished = false;
};
