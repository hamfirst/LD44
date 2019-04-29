#pragma once

#include "Game/GameCommon.h"

#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"
#include "Game/ServerObjects/GameServerObjectBase.refl.h"

#include "GameShared/Systems/GameLogicSystems.h"
#include "GameShared/GameLogicContainer.h"

#include "Runtime/ServerObject/ServerObject.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.h"
#include "Runtime/ServerObject/ServerObjectRegistrationMacros.h"

struct PickupBaseInitData : public GameServerObjectBaseInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(PickupBaseInitData);
};

class PickupBase : public GameServerObjectBase
{
public:
  DECLARE_SERVER_OBJECT;

  PickupBase() = default;
  PickupBase(const PickupBase & rhs) = default;
  PickupBase(PickupBase && rhs) = default;

  PickupBase & operator = (const PickupBase & rhs) = default;
  PickupBase & operator = (PickupBase && rhs) = default;

  void Init(const PickupBaseInitData & init_data, GameLogicContainer & game_container);
  void UpdateFirst(GameLogicContainer & game_container);
  void UpdateMiddle(GameLogicContainer & game_container);

  virtual bool CanBePickedUp(NotNullPtr<ServerObject> server_object, GameLogicContainer & game_container);
  virtual void PickUp(NotNullPtr<ServerObject> server_object, GameLogicContainer & game_container);

public:


private:
  bool m_PickedUp = false;
};
