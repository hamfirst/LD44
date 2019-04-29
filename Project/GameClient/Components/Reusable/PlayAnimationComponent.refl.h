
#pragma once

#include "GameClient/GameClientCommon.h"
#include "Runtime/Component/ComponentInitData.refl.h"
#include "Engine/Component/Component.h"

enum STORM_REFL_ENUM class PlayAnimationComponentLoopMode
{
  kPlayLooping,
  kPlayOnceAndDestroy,
};

struct PlayAnimationComponentInitData : public ComponentInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(PlayAnimationComponentInitData);

  RString m_Animation = "Animation";
  uint32_t STORM_REFL_IGNORE m_AnimationHash = 0;
  REnum<PlayAnimationComponentLoopMode> m_LoopMode = PlayAnimationComponentLoopMode::kPlayLooping;
};

class PlayAnimationComponent : public Component
{
public:
  DECLARE_COMPONENT;

  PlayAnimationComponent(PlayAnimationComponentInitData && init_data);
  virtual ~PlayAnimationComponent();

  void UpdateFirst();

private:
  uint32_t m_AnimationHash;
  PlayAnimationComponentLoopMode m_LoopMode;
};
