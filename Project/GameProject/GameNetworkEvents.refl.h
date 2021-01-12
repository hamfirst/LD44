#pragma once

#include <StormNet/NetReflectionStruct.h>
#include <StormNet/NetReflectionTypeDatabase.h>

#include <StormNet/NetReflection.h>

#include "GameProject/GameServerTypes.h"

#include "ProjectSettings/ProjectNetworkSettings.h"
#include "ProjectSettings/ProjectPerspective.h"

struct GlobalNetworkEvent
{
  NET_DECLARE_BASE_TYPE;
  NET_REFL;
};

struct CreateEntityGlobalEvent : public GlobalNetworkEvent
{
  NET_REFL;
  uint32_t m_AssetHash;
  int16_t m_PositionX;
  int16_t m_PositionY;
};

struct CameraShakeEvent : public GlobalNetworkEvent
{
  NET_REFL;
};

struct PlaySoundGlobalEvent : public GlobalNetworkEvent
{
  NET_REFL;
  uint32_t m_AssetHash;
  int16_t m_PositionX;
  int16_t m_PositionY;

  // Vampire
  bool m_Noisy;
};

enum STORM_REFL_ENUM class GlobalVfxType
{
  kMuzzleFlash,
};

struct PlayVfxGlobalEvent : public GlobalNetworkEvent
{
  NET_REFL;
  uint32_t m_AssetHash;
  int16_t m_PositionX;
  int16_t m_PositionY;
};

struct PlayVfxAttachedGlobalEvent  : public GlobalNetworkEvent
{
  NET_REFL;
  uint32_t m_AssetHash;
  int16_t m_PositionX;
  int16_t m_PositionY;
  int8_t m_Index;
};

struct PlayVfxSpriteGlobalEvent  : public GlobalNetworkEvent
{
  NET_REFL;
  uint32_t m_AssetHash;
  uint32_t m_AnimationHash;
  int16_t m_PositionX;
  int16_t m_PositionY;
};

struct PlayVfxSpriteAttachedGlobalEvent  : public GlobalNetworkEvent
{
  NET_REFL;
  uint32_t m_AssetHash;
  uint32_t m_AnimationHash;
  int16_t m_PositionX;
  int16_t m_PositionY;
  int8_t m_Index;
};

struct MuzzleFlashEvent : public GlobalNetworkEvent
{
  NET_REFL;
  int8_t m_Index;
  GameNetVal m_Angle;
};

struct ProjectileImpactEvent : public GlobalNetworkEvent
{
  NET_REFL;
  bool m_HitCharacter = false;
  int16_t m_PositionX;
  int16_t m_PositionY;
};

struct TieEvent : public GlobalNetworkEvent
{
  NET_REFL;
};


struct ServerAuthNetworkEvent
{
  NET_DECLARE_BASE_TYPE;
  NET_REFL;
};

struct PlaceholderServerAuthEvent : public ServerAuthNetworkEvent
{
  NET_REFL;
};

struct TargetNetworkEvent
{
  NET_DECLARE_BASE_TYPE;
  NET_REFL;
  NetRangedNumber<int, 0, 255> m_Target;
};

struct PlaceholderTargetEvent : public TargetNetworkEvent
{
  NET_REFL;
};

struct ClientNetworkEvent
{
  NET_DECLARE_BASE_TYPE;
  NET_REFL;
};

struct PlaceholderClientEvent : public ClientNetworkEvent
{
  NET_REFL;
};

#if PROJECT_PERSPECTIVE == PERSPECTIVE_SIDESCROLLER
struct JumpEvent : public ClientNetworkEvent
{
  NET_REFL;
};
#endif

#ifdef NET_USE_AIM_DIRECTION
struct FireEvent : public ClientNetworkEvent
{
  NET_REFL;
};
#endif

struct UseEvent : public ClientNetworkEvent
{
  NET_REFL;
};

struct PurchaseEvent : public ClientNetworkEvent
{
  NET_REFL;
  int16_t m_Upgrade;
};


