
#pragma once

#include "GameProject/GameCommon.h"
#include "GameProject/GameplayEvents/DamageType.refl.h"

#include "GameProject/ServerEntities/CharacterFacing.refl.h"

#include "Runtime/SpriteBase/SpriteAnimationEventDef.refl.h"

struct DealDamageAnimationEvent : public SpriteAnimationEventDataBase
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(DealDamageAnimationEvent);

  static uint32_t TypeNameHash;

  RInt m_Amount = 20;

  REnum<CharacterFacing> m_Direction;
  REnum<DamageType> m_DamageType;
};
