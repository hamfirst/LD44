
#include "GameProject/GameCommon.h"

#include "GameProject/GameController.refl.h"
#include "GameProject/GameServerEventSender.h"

#include "GameProject/GameplayEvents/PickupEvents.h"

#include "GameProject/ServerEntities/Pickups/PickupBase.refl.h"
#include "GameProject/ServerEntities/Pickups/PickupBase.refl.meta.h"

#include "Runtime/ClientEntity/ClientEntityResource.h"

void PickupBase::Init(const PickupBaseInitData & init_data, GameServerWorld & game_world)
{

}

void PickupBase::UpdateFirst(GameServerWorld & game_world)
{

}

void PickupBase::UpdateMiddle(GameServerWorld & game_world)
{
  auto move_box = GetMoveBox();
  if(move_box)
  {
    auto event = game_container.GetServerObjectEventSystem().PushEventSource<PickupAvailableEvent>(
            move_box.Value(), EventMetaData(this, &game_container));
  }
}

bool PickupBase::CanBePickedUp(NotNullPtr<ServerEntity> server_object, GameServerWorld & game_world)
{
  return m_PickedUp == false;
}

void PickupBase::PickUp(NotNullPtr<ServerEntity> server_object, GameServerWorld & game_world)
{
  m_PickedUp = true;
  Destroy(game_container.GetObjectManager());
}
