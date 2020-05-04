#pragma once

#include "Game/GameCommon.h"

#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"
#include "Game/ServerEntities/GameServerEntityBase.refl.h"

#include "GameShared/Systems/GameLogicSystems.h"
#include "GameShared/GameServerWorld.h"

#include "Runtime/ServerEntity/ServerEntity.h"
#include "Runtime/ServerEntity/ServerEntityInitData.refl.h"
#include "Runtime/ServerEntity/ServerEntityRegistrationMacros.h"

struct PickupBaseInitData : public GameServerEntityBaseInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(PickupBaseInitData);
};

class PickupBase : public GameServerEntityBase
{
public:
  DECLARE_SERVER_ENTITY;

  PickupBase() = default;
  PickupBase(const PickupBase & rhs) = default;
  PickupBase(PickupBase && rhs) = default;

  PickupBase & operator = (const PickupBase & rhs) = default;
  PickupBase & operator = (PickupBase && rhs) = default;

  void Init(const PickupBaseInitData & init_data, GameServerWorld & game_container);
  void UpdateFirst(GameServerWorld & game_container);
  void UpdateMiddle(GameServerWorld & game_container);

  virtual bool CanBePickedUp(NotNullPtr<ServerEntity> server_object, GameServerWorld & game_container);
  virtual void PickUp(NotNullPtr<ServerEntity> server_object, GameServerWorld & game_container);

public:


private:
  bool m_PickedUp = false;
};
