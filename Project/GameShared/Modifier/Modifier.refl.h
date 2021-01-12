
#pragma once

#include "StormRefl/StormRefl.h"
#include "GameShared/GameSharedCommon.h"
#include "GameProject/GameServerTypes.h"

enum STORM_REFL_ENUM class ModifierType
{
  kAdd,
  kSubtract,
  kMultiply,
  kDivide,
  kSet,
};


struct Modifier
{
  ModifierType m_Type;
  GameNetVal m_Value;
};

struct ModifierConfigElement
{
  STORM_DATA_DEFAULT_CONSTRUCTION(ModifierConfigElement);
  REnum<ModifierType> m_Type;
  RDeterministicFloat<GameNetVal> m_Value;
};

void ApplyModifier(int & val, ModifierType type, GameNetVal mod);
void ApplyModifier(float & val, ModifierType type, GameNetVal mod);
void ApplyModifier(GameNetVal & val, ModifierType type, GameNetVal mod);

void ApplyModifier(int & val, Modifier & elem);
void ApplyModifier(float & val, Modifier & elem);
void ApplyModifier(GameNetVal & val, Modifier & elem);

void ApplyModifier(int & val, ModifierConfigElement & elem);
void ApplyModifier(float & val, ModifierConfigElement & elem);
void ApplyModifier(GameNetVal & val, ModifierConfigElement & elem);


