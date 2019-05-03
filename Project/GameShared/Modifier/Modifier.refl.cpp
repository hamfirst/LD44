

#include "GameShared/Modifier/Modifier.refl.meta.h"

void ApplyModifier(int & val, ModifierType type, GameNetVal mod)
{
  GameNetVal v(val);
  ApplyModifier(v, type, mod);
  val = (int)v;
}

void ApplyModifier(float & val, ModifierType type, GameNetVal mod)
{
  auto elem_val = (float)mod;
  switch((ModifierType)type)
  {
    case ModifierType::kAdd:
      val += elem_val;
      break;
    case ModifierType::kSubtract:
      val -= elem_val;
      break;
    case ModifierType::kMultiply:
      val *= elem_val;
      break;
    case ModifierType::kDivide:
      val /= elem_val;
      break;
  }
}

void ApplyModifier(GameNetVal & val, ModifierType type, GameNetVal mod)
{
  switch(type)
  {
    case ModifierType::kAdd:
      val += mod;
      break;
    case ModifierType::kSubtract:
      val -= mod;
      break;
    case ModifierType::kMultiply:
      val *= mod;
      break;
    case ModifierType::kDivide:
      val /= mod;
      break;
  }
}

void ApplyModifier(int & val, Modifier & elem)
{
  ApplyModifier(val, elem.m_Type, elem.m_Value);
}

void ApplyModifier(float & val, Modifier & elem)
{
  ApplyModifier(val, elem.m_Type, elem.m_Value);
}

void ApplyModifier(GameNetVal & val, Modifier & elem)
{
  ApplyModifier(val, elem.m_Type, elem.m_Value);
}

void ApplyModifier(int & val, ModifierConfigElement & elem)
{
  ApplyModifier(val, elem.m_Type, elem.m_Value);
}

void ApplyModifier(float & val, ModifierConfigElement & elem)
{
  ApplyModifier(val, elem.m_Type, elem.m_Value);
}

void ApplyModifier(GameNetVal & val, ModifierConfigElement & elem)
{
  ApplyModifier(val, elem.m_Type, elem.m_Value);
}
