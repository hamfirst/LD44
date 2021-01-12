#pragma once

#include "GameProject/GameCommon.h"

#include "GameProject/ServerEntities/Pickups/PickupBase.refl.h"

#include "Runtime/ServerEntity/ServerEntity.h"
#include "Runtime/ServerEntity/ServerEntityInitData.refl.h"
#include "Runtime/ServerEntity/ServerEntityRegistrationMacros.h"

struct HealthPickupInitData : public PickupBaseInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(HealthPickupInitData);
};

class HealthPickup : public PickupBase
{
public:
  DECLARE_SERVER_ENTITY;

  HealthPickup() = default;
  HealthPickup(const HealthPickup & rhs) = default;
  HealthPickup(HealthPickup && rhs) = default;

  HealthPickup & operator = (const HealthPickup & rhs) = default;
  HealthPickup & operator = (HealthPickup && rhs) = default;

  bool CanBePickedUp(NotNullPtr<ServerEntity> server_object, GameServerWorld & game_world) override;
  void PickUp(NotNullPtr<ServerEntity> server_object, GameServerWorld & game_world) override;

  virtual czstr GetDefaultEntityBinding() const override;
  virtual const SpritePtr & GetSprite() const override;
public:

  ServerEntityHandle m_AvoidObject;
};
