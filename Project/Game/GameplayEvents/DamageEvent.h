#pragma once

#include "Runtime/Event/Event.h"

#include "Game/GameplayEvents/DamageType.refl.h"
#include "Game/ServerObjects/CharacterFacing.refl.h"

struct DamageEvent
{
  DECLARE_EVENT(DamageEvent);

  int m_Amount = 1;
  CharacterFacing m_Direction;
  int m_Source = -1;
  uint32_t m_AttackId = 0;

  DamageType m_DamageType = DamageType::kMelee;
};

