
#include "Game/GameCommon.h"

#include "Game/GameController.refl.h"
#include "Game/GameServerEventSender.h"

#include "Game/ServerEntities/Pickups/HealthPickup/HealthPickup.refl.h"
#include "Game/ServerEntities/Pickups/HealthPickup/HealthPickup.refl.meta.h"

#include "Game/ServerEntities/Player/PlayerServerEntity.refl.h"


#include "Runtime/ClientEntity/ClientEntityResource.h"

czstr g_HealthPickupEntityFile = "./Gameplay/HealthPickup.entity";
GLOBAL_ASSET(ClientEntityResourcePtr, g_HealthPickupEntityFile, g_HealthPickupEntity);

CLIENT_ASSET(ClientAssetType::kAudio, "./Sounds/HealthPickedUp.wav", g_HealthPickupSfx);

bool HealthPickup::CanBePickedUp(NotNullPtr<ServerEntity> server_object, GameServerWorld & game_container)
{
  if(server_object == m_AvoidObject.Resolve(game_container.GetObjectManager()))
  {
    return false;
  }

  return server_object->CastTo<PlayerServerEntity>();
}

void HealthPickup::PickUp(NotNullPtr<ServerEntity> server_object, GameServerWorld & game_container)
{
  auto player = server_object->CastTo<PlayerServerEntity>();
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

