
#include "GameClient/GameClientCommon.h"
#include "GameClient/GameContainer.h"

#include "Runtime/ServerEntity/ServerEntity.h"
#include "Runtime/ClientEntity/ClientEntityResource.h"
#include "Runtime/VisualEffect/VisualEffectResource.h"
#include "Runtime/Asset/Asset.h"

#include "Engine/Entity/ClientEntity.h"
#include "Engine/Asset/AudioAsset.h"

#include "GameClient/ClientComponents/Reusable/PlayAnimationComponent.refl.h"
#include "GameClient/ClientComponents/Reusable/PlayAnimationComponent.refl.meta.h"

PlayAnimationComponent::PlayAnimationComponent(PlayAnimationComponentInitData && init_data)
{
  if(init_data.m_AnimationHash != 0)
  {
    m_AnimationHash = init_data.m_AnimationHash;
  }
  else
  {
    m_AnimationHash = crc32(init_data.m_Animation.data());
  }

  m_LoopMode = init_data.m_LoopMode;
}

PlayAnimationComponent::~PlayAnimationComponent()
{
  
}

void PlayAnimationComponent::UpdateFirst()
{
  switch (m_LoopMode)
  {
  case PlayAnimationComponentLoopMode::kPlayLooping:
    GetEntity()->FrameAdvance(m_AnimationHash);
    break;
  case PlayAnimationComponentLoopMode::kPlayOnceAndDestroy:
    if (GetEntity()->FrameAdvance(m_AnimationHash, false))
    {
      GetEntity()->Destroy();
      return;
    }
    break;
  default:
    break;
  }
}
