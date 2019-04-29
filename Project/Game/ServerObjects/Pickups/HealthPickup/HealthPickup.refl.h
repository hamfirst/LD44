#pragma once

#include "Game/GameCommon.h"

#include "Game/ServerObjects/Pickups/PickupBase.refl.h"

#include "Runtime/ServerObject/ServerObject.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.h"
#include "Runtime/ServerObject/ServerObjectRegistrationMacros.h"

struct HealthPickupInitData : public PickupBaseInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(HealthPickupInitData);
};

class HealthPickup : public PickupBase
{
public:
  DECLARE_SERVER_OBJECT;

  HealthPickup() = default;
  HealthPickup(const HealthPickup & rhs) = default;
  HealthPickup(HealthPickup && rhs) = default;

  HealthPickup & operator = (const HealthPickup & rhs) = default;
  HealthPickup & operator = (HealthPickup && rhs) = default;

  bool CanBePickedUp(NotNullPtr<ServerObject> server_object, GameLogicContainer & game_container) override;
  void PickUp(NotNullPtr<ServerObject> server_object, GameLogicContainer & game_container) override;

  virtual czstr GetDefaultEntityBinding() const override;
  virtual const SpritePtr & GetSprite() const override;
public:

  ServerObjectHandle m_AvoidObject;
};
