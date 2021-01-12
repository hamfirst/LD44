#pragma once

#include <memory>
#include <vector>

#include "Foundation/SkipField/SkipFieldIterator.h"
#include "Runtime/Event/Event.h"
#include "Runtime/Event/EventSystem.h"
#include "Runtime/Event/EventDispatcher.h"
#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Animation/AnimationState.h"

#include "Engine/Entity/ClientEntityHandle.h"
#include "Engine/ClientComponent/ClientComponentHandle.h"

#include "Runtime/ServerEntity/ServerEntityHandle.h"

class EngineState;
class ClientComponent;
class ClientEntity;
class ServerEntity;
class GameContainer;
class RenderState;

using EntityEventSystem = EventSystem<ClientEntity, ClientEntityHandle>;
extern template class EventSystem<ClientEntity, ClientEntityHandle>;

using EntityEventDispatch = EventDispatch<ClientEntity, ClientComponentHandle>;
extern template class EventDispatch<ClientEntity, ClientComponentHandle>;

using EntityCustomDraw = Delegate<void, const Box &, const RenderVec2 &, RenderState &>;

class ENGINE_EXPORT ClientEntity
{
public:
  ClientEntity(NotNullPtr<EngineState> engine_state, NotNullPtr<EntityEventSystem> event_system,
          const ServerEntityHandle & server_object, NullOptPtr<const ServerEntityManager> obj_manager, NotNullPtr<GameContainer> game);
  ~ClientEntity();

  ClientEntity(const ClientEntity & rhs) = delete;
  ClientEntity(ClientEntity && rhs) = delete;

  ClientEntity & operator = (const ClientEntity & rhs) = delete;
  ClientEntity & operator = (ClientEntity && rhs) = delete;

  template <typename Component>
  NotNullPtr<Component> AddComponent()
  {
    return static_cast<Component *>(AddComponentInternal(Component::TypeIndex, nullptr));
  }

  template <typename Component, typename InitData>
  NotNullPtr<Component> AddComponent(InitData && init_data)
  {
    return static_cast<Component *>(AddComponentInternal(Component::TypeIndex, &init_data));
  }

  template <typename Component>
  NullOptPtr<Component> FindComponent()
  {
    return static_cast<Component *>(FindComponentInternal(Component::TypeNameHash));
  }

  template <typename Component>
  NullOptPtr<Component> FindComponentThatImplements()
  {
    return static_cast<Component *>(FindComponentThatImplementsInternal(Component::TypeNameHash));
  }

  template <typename Event, typename ... InitArgs>
  NotNullPtr<Event> PushEvent(const Box & box, InitArgs && ... init_args)
  {
    m_EventSystem->PushEventSource<Event>(box, std::forward<InitArgs>(init_args)...);
  }

  template <typename Event>
  void PushEventReceiver(const Box & box)
  {
    m_EventSystem->PushEventReceiver(this, box, Event::TypeNameHash);
  }

  bool TriggerEventHandler(uint32_t event_type, const void * ev, const EventMetaData & meta);

  NotNullPtr<EngineState> GetEngineState();
  NotNullPtr<GameContainer> GetGameContainer();

  SpritePtr & GetSprite();
  void SetSprite(const SpritePtr & sprite);
  Vector2f & GetPosition();
  void SetPosition(const Vector2f & position);
  int & GetLayer();
  void SetLayer(int layer);
  std::string & GetName();
  uint64_t GetAssetNameHash();
  AnimationState & GetAnimationState();
  EntityRenderState & GetRenderState();
  void SetSkinName(uint32_t skin_name_hash);

  void SetDefaultFrame();
  bool FrameAdvance(uint32_t anim_name_hash, bool loop = true);
  bool SyncToFrame(uint32_t anim_name_hash, int frame);
  Box GetDrawingFrame() const;
  void SetParent(NullOptPtr<ClientEntity> entity);

  void SetRotation(bool flip_x, bool flip_y, float rotation = 0);
  void SetCustomDrawingCallback(EntityCustomDraw && draw_callback);
  void ClearCustomDrawingCallback();

  void Destroy();

  ClientEntityHandle GetHandle() const;

protected:

  friend class ClientEntitySystem;
  friend class ClientComponent;
  friend class MapInstance;
  friend class GameClientEntitySync;

  template <typename Type>
  friend class SkipField;

  void SetHandle(Handle & handle);
  void SetIterator(const SkipFieldIterator & itr);
  const SkipFieldIterator & GetIterator() const;

  void Activate();
  bool IsActivated() const;

  void ServerUpdate();
  void ServerDestroy();

  void AddToChildList(NotNullPtr<ClientEntity> entity);
  void RemoveFromChildList(NotNullPtr<ClientEntity> entity);
  void UpdateChildListBucket();
  void UpdateBucket(int bucket);

  void AddComponentInternal(NotNullPtr<ClientComponent> component);
  ClientComponent * AddComponentInternal(std::size_t type_index, void * init_data);
  void RemoveComponentInternal(NotNullPtr<ClientComponent> component);
  NullOptPtr<ClientComponent> FindComponentInternal(uint32_t component_type_name_hash);
  NullOptPtr<ClientComponent> FindComponentThatImplementsInternal(uint32_t component_type_name_hash);
  
  void RemoveEventHandler(uint32_t handler_key);

  NullOptPtr<ServerEntityManager> GetServerEntityManager();
  NullOptPtr<ServerEntityManager> GetServerEntityManager(int history_index);
  
private:
  NotNullPtr<EngineState> m_EngineState;
  NotNullPtr<EntityEventSystem> m_EventSystem;
  NotNullPtr<GameContainer> m_GameContainer;

  NullOptPtr<ClientEntity> m_Parent;
  int m_Bucket;
  bool m_Activated;

  SpritePtr m_Sprite;
  EntityCustomDraw m_CustomDraw;

  Vector2f m_Position;
  Optional<Vector2f> m_PrevPosition;
  int m_Layer;
  EntityRenderState m_RenderState;
  std::string m_Name;
  uint64_t m_AssetHash;

  ClientEntityHandle m_Handle;
  SkipFieldIterator m_Iterator;

  NullOptPtr<const ServerEntityManager> m_ServerEntityManager;
  ServerEntityHandle m_ServerObject;

  std::vector<std::pair<uint32_t, NotNullPtr<ClientComponent>>> m_Components;
  std::vector<NotNullPtr<ClientEntity>> m_ChildEntities;
  EntityEventDispatch m_EventDispatch;
};



