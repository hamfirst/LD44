#pragma once

#include <memory>

#include "Foundation/Optional/NullOpt.h"
#include "Foundation/Any/Any.h"

#include "Runtime/ServerEntity/ServerEntityHandle.h"

class CollisionSystem;
class ClientEntitySystem;
class ClientEntity;
class ClientEntityResource;
class ClientComponentSystem;
class ClientComponent;
class MapSystem;
class MapResource;
class MapInstance;
class VisualEffectManager;

class ClientComponentUpdateBucketList;
class ServerEntity;
class GameContainer;
class UIManager;
class Window;

class EngineState
{
public:

  EngineState(NotNullPtr<GameContainer> game, Window & window);
  ~EngineState();

  NotNullPtr<ClientEntity> CreateEntity();
  NotNullPtr<ClientEntity> CreateEntity(NotNullPtr<ClientEntityResource> resource,
          NullOptPtr<const ServerEntity> server_object = nullptr,
          NullOptPtr<const ServerEntityManager> obj_manager = nullptr, bool activate = true);

  void DestroyAllEntities();
  void DestroyAllGameplayObjects();

  std::size_t LoadMap(NotNullPtr<MapResource> map);
  NullOptPtr<MapInstance> GetMapInstance(std::size_t map_id);
  void UnloadMap(std::size_t map_id);

  template <typename T>
  void VisitComponents(Delegate<void, NotNullPtr<T>> & cb);

  NotNullPtr<ClientEntitySystem> GetEntitySystem();
  NotNullPtr<ClientComponentSystem> GetComponentSystem();
  NotNullPtr<MapSystem> GetMapSystem();
  NotNullPtr<VisualEffectManager> GetVisualEffectManager();
  NotNullPtr<UIManager> GetUIManager();

private:

  friend class ClientEntity;
  friend class ClientEntitySystem;
  friend class MapRenderer;
  friend class MapInstance;
  friend class Camera;

  std::unique_ptr<ClientEntitySystem> m_EntitySystem;
  std::unique_ptr<ClientComponentSystem> m_ComponentSystem;
  std::unique_ptr<MapSystem> m_MapSystem;
  std::unique_ptr<VisualEffectManager> m_VisualEffectManager;
  std::unique_ptr<UIManager> m_UIManager;
};

