#pragma once

#include "GameProject/GameCommon.h"

#include "GameProject/GameServerEventSender.h"
#include "GameProject/GameStage.h"
#include "GameProject/ServerEntities/GameServerEntityBase.refl.h"

#include "Project/GameServerFramework/GameServerWorld.h"

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

  void Init(const PickupBaseInitData & init_data, GameServerWorld & game_world);
  void UpdateFirst(GameServerWorld & game_world);
  void UpdateMiddle(GameServerWorld & game_world);

  virtual bool CanBePickedUp(NotNullPtr<ServerEntity> server_object, GameServerWorld & game_world);
  virtual void PickUp(NotNullPtr<ServerEntity> server_object, GameServerWorld & game_world);

public:


private:
  bool m_PickedUp = false;
};
