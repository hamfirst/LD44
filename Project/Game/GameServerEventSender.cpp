
#include "Game/GameCommon.h"
#include "Game/GameServerEventSender.h"

void GameServerEventSender::SendCreateEntity(const GameNetVec2 & pos, uint32_t asset_hash)
{
  if (ReconcileEvent<PlaySoundGlobalEvent>(pos, asset_hash) == false)
  {
    return;
  }

  CreateEntityGlobalEvent ev;
  ev.m_PositionX = (int16_t)((int32_t)pos.x);
  ev.m_PositionY = (int16_t)((int32_t)pos.y);
  ev.m_AssetHash = asset_hash;
  BroadcastEvent(ev);
}

void GameServerEventSender::SendCameraShake(const GameNetVec2 & pos)
{
  if (ReconcileEvent<CameraShakeEvent>(pos) == false)
  {
    return;
  }

  CameraShakeEvent ev;
  BroadcastEvent(ev);
}

void GameServerEventSender::SendSoundEvent(const GameNetVec2 & pos, uint32_t asset_hash, bool noisy)
{
  if (ReconcileEvent<PlaySoundGlobalEvent>(pos, (int)asset_hash) == false)
  {
    return;
  }

  PlaySoundGlobalEvent ev;
  ev.m_PositionX = (int16_t)((int32_t)pos.x);
  ev.m_PositionY = (int16_t)((int32_t)pos.y);
  ev.m_AssetHash = asset_hash;
  ev.m_Noisy = noisy;
  BroadcastEvent(ev);
}

void GameServerEventSender::SendSoundEvent(const GameNetVec2 & pos, const GameNetVec2 & normal, uint32_t asset_hash, bool noisy)
{
  if (ReconcileEvent<PlaySoundGlobalEvent>(pos, normal, (int16_t)asset_hash) == false)
  {
    return;
  }

  PlaySoundGlobalEvent ev;
  ev.m_PositionX = (int16_t)((int32_t)pos.x);
  ev.m_PositionY = (int16_t)((int32_t)pos.y);
  ev.m_AssetHash = asset_hash;
  ev.m_Noisy = noisy;
  BroadcastEvent(ev);
}

void GameServerEventSender::SendVfxEvent(const GameNetVec2 & pos, uint32_t asset_hash)
{
  if (ReconcileEvent<PlayVfxGlobalEvent>(pos, asset_hash) == false)
  {
    return;
  }

  PlayVfxGlobalEvent ev;
  ev.m_PositionX = (int16_t)((int32_t)pos.x);
  ev.m_PositionY = (int16_t)((int32_t)pos.y);
  ev.m_AssetHash = asset_hash;
  BroadcastEvent(ev);
}

void GameServerEventSender::SendVfxEvent(const GameNetVec2 & pos, const GameNetVec2 & normal, uint32_t asset_hash)
{
  if (ReconcileEvent<PlayVfxGlobalEvent>(pos, normal, (int16_t)asset_hash) == false)
  {
    return;
  }

  PlayVfxGlobalEvent ev;
  ev.m_PositionX = (int16_t)((int32_t)pos.x);
  ev.m_PositionY = (int16_t)((int32_t)pos.y);
  ev.m_AssetHash = asset_hash;
  BroadcastEvent(ev);
}

void GameServerEventSender::SendVfxSpriteEvent(const GameNetVec2 & pos, uint32_t asset_hash, uint32_t animation_hash)
{
  uint64_t event_id = ((uint64_t)asset_hash << 32) | (uint64_t)animation_hash;
  if (ReconcileEvent<PlayVfxSpriteGlobalEvent>(pos, event_id) == false)
  {
    return;
  }

  PlayVfxSpriteGlobalEvent ev;
  ev.m_PositionX = (int16_t)((int32_t)pos.x);
  ev.m_PositionY = (int16_t)((int32_t)pos.y);
  ev.m_AssetHash = asset_hash;
  ev.m_AnimationHash = animation_hash;
  BroadcastEvent(ev);
}

void GameServerEventSender::SendVfxSpriteAttachedEvent(int player_index, const GameNetVec2 & pos, uint32_t asset_hash, uint32_t animation_hash)
{
  uint64_t event_id = ((uint64_t)asset_hash << 32) | (uint64_t)animation_hash + player_index;
  if (ReconcileEvent<PlayVfxSpriteAttachedGlobalEvent>(pos, event_id) == false)
  {
    return;
  }

  PlayVfxSpriteAttachedGlobalEvent ev;
  ev.m_PositionX = (int16_t)((int32_t)pos.x);
  ev.m_PositionY = (int16_t)((int32_t)pos.y);
  ev.m_AssetHash = asset_hash;
  ev.m_AnimationHash = animation_hash;
  ev.m_Index = player_index;
  BroadcastEvent(ev);
}

void GameServerEventSender::SendMuzzleFlashEvent(int player_index, GameNetVal angle)
{
  if (ReconcileEvent<MuzzleFlashEvent>(player_index) == false)
  {
    return;
  }

  MuzzleFlashEvent ev;
  ev.m_Index = player_index;
  ev.m_Angle = angle;
  BroadcastEvent(ev);
}

void GameServerEventSender::SendProjectileImpactEvent(bool hit_character, const GameNetVec2 & pos)
{
  if (ReconcileEvent<MuzzleFlashEvent>(pos) == false)
  {
    return;
  }

  ProjectileImpactEvent ev;
  ev.m_HitCharacter = hit_character;
  ev.m_PositionX = (int16_t)((int32_t)pos.x);
  ev.m_PositionY = (int16_t)((int32_t)pos.y);
  BroadcastEvent(ev);
}