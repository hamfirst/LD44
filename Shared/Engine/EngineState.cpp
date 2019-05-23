
#include "Engine/EngineCommon.h"
#include "Engine/EngineState.h"

#include "Engine/Entity/ClientEntitySystem.h"
#include "Engine/ClientComponent/ClientComponentSystem.h"
#include "Engine/Map/MapSystem.h"
#include "Engine/VisualEffect/VisualEffectManager.h"
#include "Engine/UI/UIManager.h"

#include "Runtime/Map/MapResource.h"

EngineState::EngineState(NotNullPtr<GameContainer> game, Window & window) :
  m_EntitySystem(std::make_unique<ClientEntitySystem>(this, game)),
  m_ComponentSystem(std::make_unique<ClientComponentSystem>()),
  m_MapSystem(std::make_unique<MapSystem>(this)),
  m_VisualEffectManager(std::make_unique<VisualEffectManager>()),
  m_UIManager(std::make_unique<UIManager>(window))
{

}

EngineState::~EngineState()
{
  m_MapSystem->UnloadAllMaps();
}

NotNullPtr<ClientEntity> EngineState::CreateEntity()
{
  return m_EntitySystem->CreateEntity(true);
}

NotNullPtr<ClientEntity> EngineState::CreateEntity(NotNullPtr<ClientEntityResource> resource,
        NullOptPtr<const ServerEntity> server_object, NullOptPtr<const ServerEntityManager> obj_manager, bool activate)
{
  return m_EntitySystem->CreateEntity(resource, server_object, obj_manager, activate);
}

void EngineState::DestroyAllEntities()
{
  return m_EntitySystem->DestroyAllEntities();
}

void EngineState::DestroyAllGameplayObjects()
{
  m_EntitySystem->DestroyAllEntities();
  m_VisualEffectManager->DestroyAllEffects();
  m_MapSystem->UnloadAllMaps();
}

std::size_t EngineState::LoadMap(NotNullPtr<MapResource> map)
{
  return m_MapSystem->InstantiateMap(*map->GetData(), {});
}

NullOptPtr<MapInstance> EngineState::GetMapInstance(std::size_t map_id)
{
  return m_MapSystem->GetMapInstance(map_id);
}

void EngineState::UnloadMap(std::size_t map_id)
{
  m_MapSystem->UnloadMap(map_id);
}

NotNullPtr<ClientEntitySystem> EngineState::GetEntitySystem()
{
  return m_EntitySystem.get();
}

NotNullPtr<ClientComponentSystem> EngineState::GetComponentSystem()
{
  return m_ComponentSystem.get();
}

NotNullPtr<MapSystem> EngineState::GetMapSystem()
{
  return m_MapSystem.get();
}

NotNullPtr<VisualEffectManager> EngineState::GetVisualEffectManager()
{
  return m_VisualEffectManager.get();
}

NotNullPtr<UIManager> EngineState::GetUIManager()
{
  return m_UIManager.get();
}
