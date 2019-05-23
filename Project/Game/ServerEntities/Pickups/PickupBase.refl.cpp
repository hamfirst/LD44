
#include "Game/GameCommon.h"

#include "Game/GameController.refl.h"
#include "Game/GameServerEventSender.h"

#include "Game/GameplayEvents/PickupEvents.h"

#include "Game/ServerEntities/Pickups/PickupBase.refl.h"
#include "Game/ServerEntities/Pickups/PickupBase.refl.meta.h"

#include "Runtime/ClientEntity/ClientEntityResource.h"

void PickupBase::Init(const PickupBaseInitData & init_data, GameLogicContainer & game_container)
{

}

void PickupBase::UpdateFirst(GameLogicContainer & game_container)
{

}

void PickupBase::UpdateMiddle(GameLogicContainer & game_container)
{
  auto move_box = GetMoveBox();
  if(move_box)
  {
    auto event = game_container.GetServerObjectEventSystem().PushEventSource<PickupAvailableEvent>(
            move_box.Value(), EventMetaData(this, &game_container));
  }
}

bool PickupBase::CanBePickedUp(NotNullPtr<ServerEntity> server_object, GameLogicContainer & game_container)
{
  return m_PickedUp == false;
}

void PickupBase::PickUp(NotNullPtr<ServerEntity> server_object, GameLogicContainer & game_container)
{
  m_PickedUp = true;
  Destroy(game_container.GetObjectManager());
}
