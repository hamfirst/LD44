
#include "Game/GameCommon.h"

#include "Game/GameController.refl.h"
#include "Game/GameServerEventSender.h"

#include "Game/ServerObjects/Pickups/HealthPickup/HealthPickup.refl.h"
#include "Game/ServerObjects/Pickups/HealthPickup/HealthPickup.refl.meta.h"

#include "Game/ServerObjects/Player/PlayerServerObject.refl.h"


#include "Runtime/Entity/EntityResource.h"

czstr g_HealthPickupEntityFile = "./Entities/HealthPickup.entity";
GLOBAL_ASSET(EntityResourcePtr, g_HealthPickupEntityFile, g_HealthPickupEntity);

CLIENT_ASSET(ClientAssetType::kAudio, "./Sounds/HealthPickedUp.wav", g_HealthPickupSfx);

bool HealthPickup::CanBePickedUp(NotNullPtr<ServerObject> server_object, GameLogicContainer & game_container)
{
  if(server_object == m_AvoidObject.Resolve(game_container.GetObjectManager()))
  {
    return false;
  }

  return server_object->CastTo<PlayerServerObject>();
}

void HealthPickup::PickUp(NotNullPtr<ServerObject> server_object, GameLogicContainer & game_container)
{
  auto player = server_object->CastTo<PlayerServerObject>();
  if(player)
  {
    player->GiveHealth(4);

    game_container.GetEventSender().SendSoundEvent(m_Position, g_HealthPickupSfx, false);
  }

  PickupBase::PickUp(server_object, game_container);
}

czstr HealthPickup::GetDefaultEntityBinding() const
{
  return g_HealthPickupEntityFile;
}

const SpritePtr & HealthPickup::GetSprite() const
{
  return g_HealthPickupEntity->GetSprite();
}

