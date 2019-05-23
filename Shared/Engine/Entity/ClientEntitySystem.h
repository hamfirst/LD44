#pragma once

class ClientEntity;
class ClientEntityResource;
class EngineState;
class GameContainer;
class DrawList;
class ShaderProgram;

struct ClientEntityDef;

#include "Engine/Entity/ClientEntityHandle.h"
#include "Engine/Entity/ClientEntity.h"

class ENGINE_EXPORT ClientEntitySystem
{
public:

  ClientEntitySystem(NotNullPtr<EngineState> engine_state, NotNullPtr<GameContainer> game);
  ~ClientEntitySystem();

  NullOptPtr<ClientEntity> ResolveHandle(const ClientEntityHandle & handle);

  void FindAllEntitiesWithName(czstr name, std::vector<NotNullPtr<ClientEntity>> & outp_entities);
  void DestroyAllEntities();
  void RemoveServerEntityManagerFromAllEntities();

  void BeginFrame();
  void FinalizeEvents();

  void DrawAllEntities(const Box & viewport_bounds, DrawList & draw_list);
  void DrawEntity(NullOptPtr<ClientEntity> entity, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state);
  static void DefaultDrawEntity(NullOptPtr<ClientEntity> entity, const Box & viewport_bounds, const RenderVec2 & screen_center,
                                RenderState & render_state, ShaderProgram & shader);

  static void DefaultDrawEntity(SpritePtr & sprite, const Vector2f & pos, const EntityRenderState & entity_render_state, 
                                const Box & viewport_bounds, const RenderVec2 & screen_center, 
                                RenderState & render_state, ShaderProgram & shader);


private:

  friend class ClientEntity;
  friend class ClientEntityHandle;

  friend class EngineState;
  friend class MapInstance;

  NotNullPtr<ClientEntity> CreateEntity(bool activate);
  NotNullPtr<ClientEntity> CreateEntity(NotNullPtr<ClientEntityDef> entity_def, bool activate);
  NotNullPtr<ClientEntity> CreateEntity(NotNullPtr<ClientEntityResource> entity_resource,
          NullOptPtr<const ServerEntity> server_object, NullOptPtr<const ServerEntityManager> obj_manager, bool activate);
  void AddComponentsToEntity(NotNullPtr<ClientEntityDef> entity_def, NotNullPtr<ClientEntity> entity);

  void DestroyEntity(NotNullPtr<ClientEntity> entity);

private:
  NotNullPtr<EngineState> m_EngineState;
  NotNullPtr<GameContainer> m_GameContainer;
  void * m_EntityAllocator;

  std::unique_ptr<EntityEventSystem> m_EventSystem;
};
