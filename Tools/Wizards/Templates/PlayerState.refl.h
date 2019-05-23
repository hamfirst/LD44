#pragma once

#include ""StormNet/NetReflectionStruct.h""
#include ""StormNet/NetReflectionTypeDatabase.h""

#include ""Game/ServerObjects/Player/States/PlayerStateBase.refl.h""

class {class_name} : public PlayerStateBase, public PlayerStateEventHandler<{class_name}>
{{
public:
  DECLARE_PLAYER_STATE;

  virtual void Move(PlayerServerEntity & player, GameLogicContainer & game_container) override;
  virtual void Transition(PlayerServerEntity & player, GameLogicContainer & game_container) override;
  virtual void Animate(PlayerServerEntity & player, GameLogicContainer & game_container) override;

public:
  // Serialized variables
}};
