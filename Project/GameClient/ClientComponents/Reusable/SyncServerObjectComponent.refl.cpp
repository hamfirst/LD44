
#include "GameClient/GameClientCommon.h"
#include "GameClient/GameContainer.h"

#include "Runtime/ServerEntity/ServerEntity.h"
#include "Runtime/ClientEntity/ClientEntityResource.h"
#include "Runtime/VisualEffect/VisualEffectResource.h"
#include "Runtime/Asset/Asset.h"

#include "Engine/Entity/ClientEntity.h"
#include "Engine/Asset/AudioAsset.h"

#include "Game/ServerEntities/GameServerEntityBase.refl.h"

#include "GameClient/ClientComponents/Reusable/SyncServerObjectComponent.refl.h"
#include "GameClient/ClientComponents/Reusable/SyncServerObjectComponent.refl.meta.h"

SyncServerObjectComponent::SyncServerObjectComponent(SyncServerObjectComponentInitData && init_data)
{
  m_SyncSprite = init_data.m_SyncSprite;
}

SyncServerObjectComponent::~SyncServerObjectComponent()
{
  
}

void SyncServerObjectComponent::UpdateFirst()
{
  auto server_obj = GetEntity()->GetServerObjectAs<GameServerEntityBase>();
  auto game_container = GetEntity()->GetGameContainer()->GetInstanceData()->GetLogicContainer();

  if (server_obj)
  {
	  auto position = (Vector2)server_obj->GetPosition();
    GetEntity()->SetPosition(position);

    auto server_object_animation_state = server_obj->GetAnimationState();
    auto & entity_animation_state = GetEntity()->GetAnimationState();
    if (server_object_animation_state)
    {
      entity_animation_state = server_object_animation_state.Value();
    }

    if (m_SyncSprite)
    {
      GetEntity()->SetSprite(server_obj->GetSprite());
    }

    auto facing = server_obj->GetFacing();
    if(facing && facing.Value() == CharacterFacing::kLeft)
    {
      GetEntity()->SetRotation(true, false);
    }
    else
    {
      GetEntity()->SetRotation(false, false);
    }
  }
}

void SyncServerObjectComponent::ServerDestroy()
{
  UpdateFirst();
}
