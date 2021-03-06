
#pragma once

#include "GameProject/GameCommon.h"
#include "GameProject/GameServerTypes.h"
#include "GameProject/GameNetworkData.refl.h"

struct PlayerConfig
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(PlayerConfig);

  RString STORM_REFL_ATTR_VAL(file, entity) m_EntityFile = "./Gameplay/Player.clientent";
  RString STORM_REFL_ATTR_VAL(file, config) m_ProjectileFile = "./Configs/TestProjectile.projectileconfig";

  RDeterministicFloat<GameNetVal> m_MoveSpeed = "1.3";
  RDeterministicFloat<GameNetVal> m_MoveSpeedBat = "2.5";
  RDeterministicFloat<GameNetVal> m_MoveAccel = "5.0";

#ifdef PLATFORMER_MOVEMENT
  RDeterministicFloat<GameNetVal> m_AirControlAccel = "0.5";
  RDeterministicFloat<GameNetVal> m_JumpSpeed = "3.5";
  RDeterministicFloat<GameNetVal> m_Gravity = "0.1";
  RDeterministicFloat<GameNetVal> m_GravityJumpReduce = "0.2";
  RDeterministicFloat<GameNetVal> m_FallthroughThreshold = "0.5";
#endif
};
