#include "GameClient/GameClientCommon.h"
#include "GameClient/GameContainer.h"
#include "Project/GameClient/UI/GameClientUIManager.h"
#include "GameClient/GameClientController.refl.meta.h"
#include "GameClient/ClientComponents/Reusable/PlayAnimationComponent.refl.h"
#include "GameClient/ClientComponents/Reusable/PlayAnimationComponent.refl.meta.h"

#include "Engine/Entity/ClientEntity.h"
#include "Engine/Entity/ClientEntitySystem.h"
#include "Engine/EngineState.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/VisualEffect/VisualEffectManager.h"

#include "Runtime/ClientEntity/ClientEntityResource.h"


#include "StormRefl/StormReflMetaCall.h"

// Vampire
CLIENT_ONLY_ASSET(AssetReference<AudioAsset>, "./Sounds/GunShotA.wav", g_GunShotA);
CLIENT_ONLY_ASSET(AssetReference<AudioAsset>, "./Sounds/GunShotB.wav", g_GunShotB);
CLIENT_ONLY_ASSET(AssetReference<AudioAsset>, "./Sounds/GunShotC.wav", g_GunShotC);
CLIENT_ONLY_ASSET(AssetReference<AudioAsset>, "./Sounds/GunShotD.wav", g_GunShotD);

CLIENT_ONLY_ASSET(AssetReference<AudioAsset>, "./Sounds/GunShotDistantA.wav", g_GunShotDistantA);
CLIENT_ONLY_ASSET(AssetReference<AudioAsset>, "./Sounds/GunShotDistantB.wav", g_GunShotDistantB);
CLIENT_ONLY_ASSET(AssetReference<AudioAsset>, "./Sounds/GunShotDistantC.wav", g_GunShotDistantC);
CLIENT_ONLY_ASSET(AssetReference<AudioAsset>, "./Sounds/GunShotDistantD.wav", g_GunShotDistantD);

CLIENT_ONLY_ASSET(AssetReference<AudioAsset>, "./Sounds/RicochetA.wav", g_RicochetA);
CLIENT_ONLY_ASSET(AssetReference<AudioAsset>, "./Sounds/RicochetB.wav", g_RicochetB);
CLIENT_ONLY_ASSET(AssetReference<AudioAsset>, "./Sounds/RicochetC.wav", g_RicochetC);
CLIENT_ONLY_ASSET(AssetReference<AudioAsset>, "./Sounds/RicochetD.wav", g_RicochetD);

CLIENT_ONLY_ASSET(AssetReference<AudioAsset>, "./Sounds/BulletHitEnemy.wav", g_ProjectileImpactCharacterAudio);

CLIENT_ONLY_ASSET(VisualEffectResourcePtr, "./VisualEffects/MuzzleFlash.vfx", g_MuzzleFlash);
CLIENT_ONLY_ASSET(VisualEffectResourcePtr, "./VisualEffects/ProjectileImpact.vfx", g_ProjectileImpact);
CLIENT_ONLY_ASSET(VisualEffectResourcePtr, "./VisualEffects/ProjectileImpactCharacter.vfx", g_ProjectileImpactCharacter);

CLIENT_ONLY_ASSET(SpritePtr, "./Sprites/Spells.sprite", g_SpellsSprite);
CLIENT_ONLY_ASSET(SpritePtr, "./Sprites/Alert.sprite", g_AlertIcon);

AssetReference<AudioAsset> * g_GunShots[] = {
        &g_GunShotA,
        &g_GunShotB,
        &g_GunShotC,
        &g_GunShotD,
};

AssetReference<AudioAsset> * g_GunShotsDistant[] = {
        &g_GunShotDistantA,
        &g_GunShotDistantB,
        &g_GunShotDistantC,
        &g_GunShotDistantD,
};

AssetReference<AudioAsset> * g_Ricochets[] = {
        &g_RicochetA,
        &g_RicochetB,
        &g_RicochetC,
        &g_RicochetD,
};

static const int kNumGunShots = sizeof(g_GunShots) / sizeof(g_GunShots[0]);
static const int kNumGunShotsDistant = sizeof(g_GunShotsDistant) / sizeof(g_GunShotsDistant[0]);
static const int kNumRicochets = sizeof(g_Ricochets) / sizeof(g_Ricochets[0]);

template <typename ParamType, bool IsGlobal, bool IsAuth>
struct GameClientControllerRegister
{
  static void Register(
    GameClientController * ptr,
    std::vector<Delegate<void, const void *>> & global_events,
    std::vector<Delegate<void, const void *>> & auth_events,
    void (GameClientController::*func_ptr)(const ParamType &))
  {

  }
};

template <typename ParamType>
struct GameClientControllerRegister<ParamType, true, false>
{
  static void Register(
    GameClientController * ptr, 
    std::vector<Delegate<void, const void *>> & global_events,
    std::vector<Delegate<void, const void *>> & auth_events,
    void (GameClientController::*func_ptr)(const ParamType &))
  {
    auto class_id = GlobalNetworkEvent::__s_TypeDatabase.GetClassId<ParamType>();
    global_events[class_id] = Delegate<void, const void *>([ptr, func_ptr](const void * ev) { (ptr->*func_ptr)(*(const ParamType *)ev); });
  }
};

template <typename ParamType>
struct GameClientControllerRegister<ParamType, false, true>
{
  static void Register(
    GameClientController * ptr,
    std::vector<Delegate<void, const void *>> & client_events,
    std::vector<Delegate<void, const void *>> & auth_events,
    void (GameClientController::*func_ptr)(const ParamType &))
  {
    auto class_id = ServerAuthNetworkEvent::__s_TypeDatabase.GetClassId<ParamType>();
    auth_events[class_id] = Delegate<void, const void *>([ptr, func_ptr](const void * ev) { (ptr->*func_ptr)(*(const ParamType *)ev); });
  }
};

GameClientController::GameClientController(GameContainer & game) :
  m_GameContainer(game)
{
  auto num_global_types = GlobalNetworkEvent::__s_TypeDatabase.GetNumTypes();
  m_GlobalEventCallbacks.resize(num_global_types);

  auto num_auth_types = ServerAuthNetworkEvent::__s_TypeDatabase.GetNumTypes();
  m_AuthEventCallbacks.resize(num_auth_types);

  auto visitor = [&](auto f)
  {
    using FuncType = decltype(f);
    using ParamType = typename std::decay_t<typename FuncType::template param_info<0>::param_type>;

    static_assert(std::is_base_of<GlobalNetworkEvent, ParamType>::value || std::is_base_of<ServerAuthNetworkEvent, ParamType>::value,
      "Event handler parameter must be either a child of GlobalNetworkEvent or ServerAuthNetworkEvent");

    auto func_ptr = FuncType::GetFunctionPtr();
    GameClientControllerRegister<ParamType,
      std::is_base_of<GlobalNetworkEvent, ParamType>::value,
      std::is_base_of<ServerAuthNetworkEvent, ParamType>::value>::Register(this, m_GlobalEventCallbacks, m_AuthEventCallbacks, func_ptr);
  };

  StormReflVisitFuncs(*this, visitor);
}

void GameClientController::Connected()
{

}

void GameClientController::Disconnected()
{

}

void GameClientController::PreloadLevel()
{
  m_GameContainer.GetEngineState().DestroyAllEntities();
}

void GameClientController::CatastrophicFailure()
{
  ASSERT(false, "Bad!");
}

void GameClientController::HandleGlobalEvent(std::size_t event_class_id, const void * event_ptr)
{
  m_GlobalEventCallbacks[event_class_id].Call(event_ptr);
}

void GameClientController::HandleAuthEvent(std::size_t event_class_id, const void * event_ptr)
{
  m_AuthEventCallbacks[event_class_id].Call(event_ptr);
}

void GameClientController::HandleEntityEvent(const ServerEntityHandle & handle, std::size_t event_class_id, const void * event_ptr)
{
  m_GameContainer.GetInstanceData()->GetEntitySync().SendEntityEvent(handle, event_class_id, event_ptr);
}

void GameClientController::HandleCreateEntityGlobalEvent(const CreateEntityGlobalEvent & ev)
{
  auto entity_asset = ClientEntityResource::Find(ev.m_AssetHash);
  if (entity_asset.IsLoaded())
  {
    auto entity = m_GameContainer.GetEngineState().CreateEntity(entity_asset.GetResource());
    entity->GetPosition() = Vector2(ev.m_PositionX, ev.m_PositionY);
  }
}

void GameClientController::HandleCameraShakeEvent(const CameraShakeEvent & ev)
{
  m_GameContainer.GetClientSystems()->GetCamera().Shake(0.2f, 4.0f);
}

void GameClientController::HandlePlaySoundGlobalEvent(const PlaySoundGlobalEvent & ev)
{
  if(m_GameContainer.GetClientSystems() == nullptr)
  {
    return;
  }

  auto & camera = m_GameContainer.GetClientSystems()->GetCamera();
  auto & ui = m_GameContainer.GetClientSystems()->GetUIManager();

  auto vfx = m_GameContainer.GetEngineState().GetVisualEffectManager();

  auto ev_pos = Vector2f(ev.m_PositionX, ev.m_PositionY);
  auto offset = ev_pos - camera.GetOffsetPosition();

  auto dist = glm::length(offset);
  auto angle = atan2f(offset.y, offset.x);
  auto c = cosf(angle);

  if(ev.m_Noisy)
  {
    static const float kGlobalNoisySoundEventFalloff = 200.0f;
    static const float kGlobalSoundEventPanDistance = 200.0f;

    float volume = kGlobalNoisySoundEventFalloff / (dist + kGlobalNoisySoundEventFalloff);
    float pan = c * 0.5f * std::min(dist / kGlobalSoundEventPanDistance, 1.0f);


    auto audio_asset = AudioAsset::Find(ev.m_AssetHash);
    g_AudioManager.PlayAudio(audio_asset, VolumeCategory::kSoundEffects, volume, pan, false);

    if(dist > 200)
    {
      ui.AddNoiseAlert(angle, powf(volume, 0.4f));
    }
  }
  else
  {
    static const float kGlobalSoundEventFalloff = 50.0f;
    static const float kGlobalSoundEventPanDistance = 200.0f;
    static const float kGlobalSoundEventMaxDistance = 250.0f;

    float volume = kGlobalSoundEventFalloff / (dist + kGlobalSoundEventFalloff);
    float pan = c * 0.5f * std::min(dist / kGlobalSoundEventPanDistance, 1.0f);

    if (kGlobalSoundEventMaxDistance > 250)
    {
      return;
    }

    auto audio_asset = AudioAsset::Find(ev.m_AssetHash);
    g_AudioManager.PlayAudio(audio_asset, VolumeCategory::kSoundEffects, volume, pan, false);
  }
}

void GameClientController::HandlePlayVfxGlobalEvent(const PlayVfxGlobalEvent & ev)
{
  auto vfx_asset = VisualEffectResource::Find(ev.m_AssetHash);
  if (vfx_asset.IsLoaded())
  {
    m_GameContainer.GetEngineState().GetVisualEffectManager()->CreateVisualEffect(vfx_asset->GetData(), 1, Vector2(ev.m_PositionX, ev.m_PositionY));
  }
}

void GameClientController::HandlePlayVfxAttachedGlobalEvent(const PlayVfxAttachedGlobalEvent & ev)
{
  if(m_GameContainer.GetClientSystems() == nullptr)
  {
    return;
  }

  auto vfx_asset = VisualEffectResource::Find(ev.m_AssetHash);
  if (vfx_asset.IsLoaded() == false)
  {
    return;
  }

  auto & entity_sync = m_GameContainer.GetInstanceData()->GetEntitySync();

  auto attach_entity = entity_sync.FindEntity(ev.m_Index, *m_GameContainer.GetInstanceData());
  if(attach_entity == nullptr)
  {
    return;
  }

  auto ev_offset = Vector2f(ev.m_PositionX, ev.m_PositionY);
  auto ev_pos = attach_entity->GetPosition() + ev_offset;

  auto vfx = m_GameContainer.GetEngineState().GetVisualEffectManager();
  vfx->CreateVisualEffect(vfx_asset, 0, ev_pos);
}

void GameClientController::HandlePlayVfxSpriteGlobalEvent(const PlayVfxSpriteGlobalEvent & ev)
{
  auto sprite_asset = g_SpellsSprite;
  if (sprite_asset.IsLoaded() == false)
  {
    return;
  }

  auto ev_pos = Vector2(ev.m_PositionX, ev.m_PositionY);

  auto entity = m_GameContainer.GetEngineState().CreateEntity();
  entity->SetPosition(ev_pos);
  entity->SetSprite(sprite_asset);

  PlayAnimationComponentInitData init_data;
  init_data.m_AnimationHash = ev.m_AnimationHash;
  init_data.m_LoopMode = PlayAnimationComponentLoopMode::kPlayOnceAndDestroy;
  entity->AddComponent<PlayAnimationComponent>(std::move(init_data));
}

void GameClientController::HandlePlayVfxSpriteAttachedGlobalEvent(const PlayVfxSpriteAttachedGlobalEvent & ev)
{
  // Vampire - fix this
  auto sprite_asset = g_SpellsSprite;
  if (sprite_asset.IsLoaded() == false)
  {
    return;
  }

  auto & entity_sync = m_GameContainer.GetInstanceData()->GetEntitySync();

  auto attach_entity = entity_sync.FindEntity(ev.m_Index, *m_GameContainer.GetInstanceData());
  if(attach_entity == nullptr)
  {
    return;
  }

  auto ev_offset = Vector2f(ev.m_PositionX, ev.m_PositionY);
  auto ev_pos = attach_entity->GetPosition() + ev_offset;

  auto entity = m_GameContainer.GetEngineState().CreateEntity();
  entity->SetPosition(ev_pos);
  entity->SetSprite(sprite_asset);

  PlayAnimationComponentInitData init_data;
  init_data.m_AnimationHash = ev.m_AnimationHash;
  init_data.m_LoopMode = PlayAnimationComponentLoopMode::kPlayOnceAndDestroy;
  entity->AddComponent<PlayAnimationComponent>(std::move(init_data));
}

void GameClientController::HandleMuzzleFlashEvent(const MuzzleFlashEvent & ev)
{
  if(m_GameContainer.GetClientSystems() == nullptr)
  {
    return;
  }

  auto & camera = m_GameContainer.GetClientSystems()->GetCamera();
  auto & ui = m_GameContainer.GetClientSystems()->GetUIManager();
  auto & entity_sync = m_GameContainer.GetInstanceData()->GetEntitySync();

  auto entity = entity_sync.FindEntity(ev.m_Index, *m_GameContainer.GetInstanceData());
  if(entity == nullptr)
  {
    return;
  }

  auto vfx = m_GameContainer.GetEngineState().GetVisualEffectManager();

  auto aim_x = cosf(ev.m_Angle);
  auto aim_y = sinf(ev.m_Angle);

  auto ev_offset = Vector2f(aim_x * 5.0f, (aim_y * 3.0f) - 4.0f);
  auto ev_pos = entity->GetPosition() + ev_offset;
  auto offset = ev_pos - camera.GetOffsetPosition();
  auto dist = glm::length(offset);
  auto angle = atan2f(offset.y, offset.x);
  auto c = cosf(angle);

  float volume = 200.0f / (dist + 200.0f);
  float pan = c * 0.5f * std::min(dist / 200, 1.0f);

  AudioAsset * audio_asset = nullptr;
  if(dist > 250)
  {
    audio_asset = g_GunShotsDistant[GetRandomNumber() % kNumGunShotsDistant]->Resolve();
    volume = 200.0f / ((dist - 250) + 200.0f);
    volume *= volume;
  }
  else
  {
    audio_asset = g_GunShots[GetRandomNumber() % kNumGunShots]->Resolve();
  }

  if(dist > 200)
  {
    ui.AddNoiseAlert(angle, powf(volume, 0.4f));
  }

  g_AudioManager.PlayAudio(audio_asset, VolumeCategory::kSoundEffects, volume, pan, false);

  auto vfx_inst = vfx->CreateVisualEffect(g_MuzzleFlash, 0, ev_pos);
  vfx_inst->SetInput(COMPILE_TIME_CRC32_STR("Angle"), ev.m_Angle);
}

void GameClientController::HandleProjectileImpactEvent(const ProjectileImpactEvent & ev)
{
  if(m_GameContainer.GetClientSystems() == nullptr)
  {
    return;
  }

  auto & camera = m_GameContainer.GetClientSystems()->GetCamera();
  auto & ui = m_GameContainer.GetClientSystems()->GetUIManager();
  auto & entity_sync = m_GameContainer.GetInstanceData()->GetEntitySync();

  auto vfx = m_GameContainer.GetEngineState().GetVisualEffectManager();

  auto ev_pos = Vector2f(ev.m_PositionX, ev.m_PositionY);
  auto offset = ev_pos - camera.GetOffsetPosition();
  auto dist = glm::length(offset);
  auto angle = atan2f(offset.y, offset.x);
  auto c = cosf(angle);

  float volume = 50.0f / (dist + 50.0f);
  float pan = c * 0.5f * std::min(dist / 200, 1.0f);

  if(dist > 250)
  {
    return;
  }

  if(ev.m_HitCharacter)
  {
    g_AudioManager.PlayAudio(g_ProjectileImpactCharacterAudio, VolumeCategory::kSoundEffects, volume, pan, false);
    vfx->CreateVisualEffect(g_ProjectileImpactCharacter, 1, ev_pos);
  }
  else
  {
    auto audio_asset = g_Ricochets[GetRandomNumber() % kNumRicochets]->Resolve();
    g_AudioManager.PlayAudio(audio_asset, VolumeCategory::kSoundEffects, volume, pan, false);

    vfx->CreateVisualEffect(g_ProjectileImpact, 1, ev_pos);
  }
}

void GameClientController::HandlePlaceholderAuthEvent(const PlaceholderServerAuthEvent & ev)
{

}
