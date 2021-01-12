
#include "Engine/EngineCommon.h"

#include "Engine/EngineState.h"
#include "Engine/Entity/ClientEntity.h"
#include "Engine/Entity/ClientEntitySystem.h"
#include "Engine/ClientComponent/ClientComponent.h"
#include "Engine/ClientComponent/ClientComponentSystem.h"

#include "Foundation/Random/Random.h"

#include "Runtime/Event/EventSystem.h"
#include "Runtime/ServerEntity/ServerEntityManager.h"

#include <sb/vector.h>

template class EventSystem<ClientEntity, ClientEntityHandle>;
template class EventDispatch<ClientEntity, ClientComponentHandle>;

NullOptPtr<ServerEntityManager> GetServerEntityManager(NotNullPtr<GameContainer> game);
NullOptPtr<ServerEntityManager> GetServerEntityManager(NotNullPtr<GameContainer> game, int history_index);

ClientEntity::ClientEntity(NotNullPtr<EngineState> engine_state, NotNullPtr<EntityEventSystem> event_system,
        const ServerEntityHandle & server_object, NullOptPtr<const ServerEntityManager> obj_manager, NotNullPtr<GameContainer> game) :
  m_EngineState(engine_state),
  m_EventSystem(event_system),
  m_GameContainer(game),
  m_Parent(nullptr),
  m_Bucket(0),
  m_Activated(false),
  m_Layer(0),
  m_AssetHash(0),
  m_ServerObject(server_object),
  m_ServerEntityManager(obj_manager)
{

}

ClientEntity::~ClientEntity()
{

}

bool ClientEntity::TriggerEventHandler(uint32_t event_type, const void * ev, const EventMetaData & meta)
{
  return m_EventDispatch.TriggerEvent(event_type, ev);
}

NotNullPtr<EngineState> ClientEntity::GetEngineState()
{
  return m_EngineState;
}

NotNullPtr<GameContainer> ClientEntity::GetGameContainer()
{
  return m_GameContainer;
}

SpritePtr & ClientEntity::GetSprite()
{
  return m_Sprite;
}

void ClientEntity::SetSprite(const SpritePtr & sprite)
{
  m_Sprite = sprite;
}

Vector2f & ClientEntity::GetPosition()
{
  return m_Position;
}

void ClientEntity::SetPosition(const Vector2f & position)
{
  m_Position = position;
}

int & ClientEntity::GetLayer()
{
  return m_Layer;
}

void ClientEntity::SetLayer(int layer)
{
  m_Layer = layer;
}

std::string & ClientEntity::GetName()
{
  return m_Name;
}

uint64_t ClientEntity::GetAssetNameHash()
{
  return m_AssetHash;
}

AnimationState & ClientEntity::GetAnimationState()
{
  return m_RenderState;
}

EntityRenderState & ClientEntity::GetRenderState()
{
  return m_RenderState;
}

void ClientEntity::SetSkinName(uint32_t skin_name_hash)
{
  m_RenderState.m_SkinNameHash = skin_name_hash;
}

void ClientEntity::SetDefaultFrame()
{
  if (m_Sprite.GetResource() != nullptr)
  {
    m_Sprite.GetResource()->GetDefaultFrame(m_RenderState);
  }
  else
  {
    AnimationState & cur_state = m_RenderState;
    cur_state = AnimationState{};
  }
}

bool ClientEntity::FrameAdvance(uint32_t anim_name_hash, bool loop)
{
  if (m_Sprite.GetResource() != nullptr)
  {
    return m_Sprite.GetResource()->FrameAdvance(anim_name_hash, GetAnimationState(), loop);
  }

  return false;
}

bool ClientEntity::SyncToFrame(uint32_t anim_name_hash, int frame)
{
  if (m_Sprite.GetResource() != nullptr)
  {
    return m_Sprite.GetResource()->SyncToFrame(anim_name_hash, GetAnimationState(), frame);
  }

  return false;
}

Box ClientEntity::GetDrawingFrame() const
{
  return Box::FromFrameCenterAndSize(m_Position, Vector2(m_RenderState.m_FrameWidth, m_RenderState.m_FrameHeight));
}

void ClientEntity::SetParent(NullOptPtr<ClientEntity> entity)
{
  if (m_Parent != nullptr)
  {
    m_Parent->RemoveFromChildList(this);
  }

  m_Parent = entity;

  if (m_Parent)
  {
    m_Parent->AddToChildList(this);
    m_Bucket = m_Parent->m_Bucket + 1;
    UpdateChildListBucket();
  }
  else
  {
    m_Bucket = 0;
    UpdateChildListBucket();
  }
}

void ClientEntity::SetRotation(bool flip_x, bool flip_y, float rotation)
{
  m_RenderState.m_Matrix.x = flip_x ? -1.0f : 1.0f;
  m_RenderState.m_Matrix.y = 0;
  m_RenderState.m_Matrix.z = 0;
  m_RenderState.m_Matrix.w = flip_y ? -1.0f : 1.0f;
}

void ClientEntity::SetCustomDrawingCallback(EntityCustomDraw && draw_callback)
{
  m_CustomDraw = std::move(draw_callback);
}

void ClientEntity::ClearCustomDrawingCallback()
{
  m_CustomDraw.Clear();
}

void ClientEntity::Destroy()
{
  m_EventDispatch.ClearAllHandlers();

  auto comp_list = std::move(m_Components);
  for (auto comp : comp_list)
  {
    comp.second->Destroy();
  }

  m_EngineState->m_EntitySystem->DestroyEntity(this);
}

ClientEntityHandle ClientEntity::GetHandle() const 
{
  return m_Handle;
}

void ClientEntity::SetHandle(Handle & handle)
{
  Handle & handle_conv = m_Handle;
  handle_conv = handle;

  m_Handle.m_EntityManager = m_EngineState->m_EntitySystem.get();
}

void ClientEntity::SetIterator(const SkipFieldIterator & itr)
{
  m_Iterator = itr;
}

const SkipFieldIterator & ClientEntity::GetIterator() const
{
  return m_Iterator;
}

void ClientEntity::Activate()
{
  if (m_Activated)
  {
    return;
  }

  m_Activated = true;
  for (auto & comp : m_Components)
  {
    comp.second->OnActivate();
  }
}

void ClientEntity::ServerUpdate()
{
  if (m_Activated == false)
  {
    return;
  }

  for (auto & comp : m_Components)
  {
    comp.second->ServerUpdate();
  }
}

void ClientEntity::ServerDestroy()
{
  if (m_Activated == false)
  {
    return;
  }

  for (auto & comp : m_Components)
  {
    comp.second->ServerDestroy();
  }
}

bool ClientEntity::IsActivated() const
{
  return m_Activated;
}

void ClientEntity::AddToChildList(NotNullPtr<ClientEntity> entity)
{
  m_ChildEntities.emplace_back(entity);
}

void ClientEntity::RemoveFromChildList(NotNullPtr<ClientEntity> entity)
{
  vremove_quick(m_ChildEntities, entity);
}

void ClientEntity::UpdateChildListBucket()
{
  for (auto & elem : m_Components)
  {
    elem.second->SetBucket(m_Bucket);
  }

  for (auto & elem : m_ChildEntities)
  {
    elem->UpdateBucket(m_Bucket + 1);
  }
}

void ClientEntity::UpdateBucket(int bucket)
{
  m_Bucket = bucket;
  UpdateChildListBucket();
}

void ClientEntity::AddComponentInternal(NotNullPtr<ClientComponent> component)
{
  component->SetOwner(this);

  m_Components.push_back(std::make_pair(component->GetTypeNameHash(), component));

  if (m_Activated)
  {
    component->OnActivate();
  }
}

ClientComponent * ClientEntity::AddComponentInternal(std::size_t type_index, void * init_data)
{
  auto comp = m_EngineState->m_ComponentSystem->CreateComponent(type_index, init_data);
  AddComponentInternal(comp);
  return comp;
}

void ClientEntity::RemoveComponentInternal(NotNullPtr<ClientComponent> component)
{
  for (std::size_t index = 0, end = m_Components.size(); index < end; ++index)
  {
    if (m_Components[index].second == component)
    {
      vremove_index_quick(m_Components, index);
      break;
    }
  }

  std::size_t index = 0;
  m_EventDispatch.RemoveEventsByUserData(component->GetHandle());
}

NullOptPtr<ClientComponent> ClientEntity::FindComponentInternal(uint32_t component_type_name_hash)
{
  for (auto & elem : m_Components)
  {
    if (elem.first == component_type_name_hash)
    {
      return elem.second;
    }
  }

  return nullptr;
}

NullOptPtr<ClientComponent> ClientEntity::FindComponentThatImplementsInternal(uint32_t component_type_name_hash)
{
  for (auto & elem : m_Components)
  {
    if (elem.second->CastTo(component_type_name_hash))
    {
      return elem.second;
    }
  }

  return nullptr;
}

void ClientEntity::RemoveEventHandler(uint32_t handler_key)
{
  m_EventDispatch.RemoveEvent(handler_key);
}

NullOptPtr<ServerEntityManager> ClientEntity::GetServerEntityManager()
{
  return ::GetServerEntityManager(m_GameContainer);
}

NullOptPtr<ServerEntityManager> ClientEntity::GetServerEntityManager(int history_index)
{
  return ::GetServerEntityManager(m_GameContainer, history_index);
}
