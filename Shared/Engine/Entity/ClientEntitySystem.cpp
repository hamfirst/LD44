
#include "Engine/EngineCommon.h"

#include "Foundation/SkipField/SkipField.h"

#include "Runtime/ClientEntity/ClientEntityResource.h"
#include "Runtime/ClientEntity/ClientEntityDef.refl.h"
#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Event/EventSystem.h"

#include "Runtime/ServerEntity/ServerEntity.h"
#include "Runtime/ServerEntity/ServerEntityHandle.h"

#include "Engine/EngineState.h"
#include "Engine/Entity/ClientEntity.h"
#include "Engine/Entity/ClientEntitySystem.h"
#include "Engine/Rendering/RenderSettings.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/ClientComponent/ClientComponentSystem.h"
#include "Engine/Sprite/SpriteEngineData.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/DrawList/DrawList.h"
#include "Engine/Profiler/Profiler.h"


SkipField<ClientEntity> s_EntityAllocator;

ClientEntitySystem::ClientEntitySystem(NotNullPtr<EngineState> engine_state, NotNullPtr<GameContainer> game) :
  m_EngineState(engine_state),
  m_GameContainer(game),
  m_EventSystem(std::make_unique<EntityEventSystem>())
{
  m_EntityAllocator = new SkipField<ClientEntity>();
}

ClientEntitySystem::~ClientEntitySystem()
{
  auto allocator = static_cast<SkipField<ClientEntity> *>(m_EntityAllocator);
  delete allocator;
}

NotNullPtr<ClientEntity> ClientEntitySystem::CreateEntity(bool activate)
{
  auto allocator = static_cast<SkipField<ClientEntity> *>(m_EntityAllocator);
  auto ptr = allocator->Allocate(m_EngineState, m_EventSystem.get(), ServerEntityHandle{}, nullptr, m_GameContainer);

  if (activate)
  {
    ptr->Activate();
  }

  return ptr;
}

NotNullPtr<ClientEntity> ClientEntitySystem::CreateEntity(NotNullPtr<ClientEntityDef> entity_def, bool activate)
{
  auto allocator = static_cast<SkipField<ClientEntity> *>(m_EntityAllocator);
  auto ptr = allocator->Allocate(m_EngineState, m_EventSystem.get(), ServerEntityHandle{}, nullptr, m_GameContainer);

  if (entity_def->m_Sprite.length() > 0)
  {
    ptr->m_Sprite = SpriteResource::Load(entity_def->m_Sprite.data());
    ptr->SetDefaultFrame();
  }

  AddComponentsToEntity(entity_def, ptr);

  if (activate)
  {
    ptr->Activate();
  }

  return ptr;
}

NotNullPtr<ClientEntity> ClientEntitySystem::CreateEntity(NotNullPtr<ClientEntityResource> entity_resource,
        NullOptPtr<const ServerEntity> server_entity, NullOptPtr<const ServerEntityManager> obj_manager, bool activate)
{
  auto allocator = static_cast<SkipField<ClientEntity> *>(m_EntityAllocator);
  auto obj_handle = server_entity ? server_entity->GetEntityHandle() : ServerEntityHandle{};

  auto ptr = allocator->Allocate(m_EngineState, m_EventSystem.get(), obj_handle, obj_manager, m_GameContainer);

  ptr->m_Sprite = entity_resource->m_Sprite;
  ptr->m_AssetHash = entity_resource->m_FileNameHash;
  ptr->SetDefaultFrame();

  AddComponentsToEntity(entity_resource->GetData(), ptr);

  if (activate)
  {
    ptr->Activate();
  }

  return ptr;
}

void ClientEntitySystem::AddComponentsToEntity(NotNullPtr<ClientEntityDef> entity_def, NotNullPtr<ClientEntity> entity)
{
  for (auto elem : entity_def->m_Components)
  {
    if (elem.second.GetTypeInfo() == nullptr)
    {
      printf("Could not find component type hash 0x%08X\n", elem.second.GetTypeNameHash());
      continue;
    }

    auto & init_data = elem.second;
    if (init_data.GetValue() == nullptr)
    {
      printf("Could not find component type %s\n", elem.second.GetTypeInfo()->m_Name.data());
      continue;
    }

    auto comp = m_EngineState->m_ComponentSystem->CreateComponentFromTypeNameHash(init_data.GetTypeNameHash(), init_data.GetValue());
    if (comp == nullptr)
    {
      printf("Could not create component\n");
      continue;
    }

    entity->AddComponentInternal(comp);
  }
}

void ClientEntitySystem::DestroyEntity(NotNullPtr<ClientEntity> entity)
{
  auto allocator = static_cast<SkipField<ClientEntity> *>(m_EntityAllocator);
  allocator->Release(entity);
}

NullOptPtr<ClientEntity> ClientEntitySystem::ResolveHandle(const ClientEntityHandle & handle)
{
  auto allocator = static_cast<SkipField<ClientEntity> *>(m_EntityAllocator);
  return allocator->ResolveHandle(handle);
}

void ClientEntitySystem::FindAllEntitiesWithName(czstr name, std::vector<NotNullPtr<ClientEntity>> & outp_entities)
{
  auto allocator = static_cast<SkipField<ClientEntity> *>(m_EntityAllocator);
  allocator->VisitAll([&](ClientEntity & entity) {
    if (entity.GetName() == name)
    {
      outp_entities.push_back(&entity);
    }
  });
}

void ClientEntitySystem::DestroyAllEntities()
{
  auto allocator = static_cast<SkipField<ClientEntity> *>(m_EntityAllocator);
  allocator->VisitAll([](ClientEntity & entity) {
    entity.Destroy();
  });
}

void ClientEntitySystem::RemoveServerEntityManagerFromAllEntities()
{
  auto allocator = static_cast<SkipField<ClientEntity> *>(m_EntityAllocator);
  allocator->VisitAll([](ClientEntity & entity) {
    entity.m_ServerEntityManager = nullptr;
  });
}

void ClientEntitySystem::BeginFrame()
{
  auto visitor = [&](auto & entity)
  {
    entity.m_PrevPosition = entity.m_Position;
  };

  s_EntityAllocator.VisitAll(visitor);
}

void ClientEntitySystem::FinalizeEvents()
{
  m_EventSystem->FinalizeEvents();
}

void ClientEntitySystem::DrawAllEntities(const Box & viewport_bounds, DrawList & draw_list)
{
  auto entity_alloc = static_cast<SkipField<ClientEntity> *>(m_EntityAllocator);

  entity_alloc->VisitAll([&](ClientEntity & entity)
  {
    auto & pos = entity.GetPosition();
    auto & render_state = entity.GetRenderState();
    if (render_state.m_Draw == false || entity.m_Activated == false)
    {
      return;
    }

    if (pos.x + render_state.m_FrameWidth / 2 < viewport_bounds.m_Start.x ||
      pos.y + render_state.m_FrameHeight / 2 < viewport_bounds.m_Start.y ||
      pos.x - render_state.m_FrameWidth / 2 > viewport_bounds.m_End.x ||
      pos.y - render_state.m_FrameHeight / 2 > viewport_bounds.m_End.y)
    {
      return;
    }

#ifdef USE_Z_ORDERING
    int draw_order = ((int)pos.y - render_state.m_FrameHeight / 2 + render_state.m_LowerEdge);
#else
    int draw_order = 0;
#endif

    draw_list.PushDraw(entity.GetLayer(), draw_order, [this, e = &entity](GameContainer & game_container, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state)
    {      
      PROFILE_SCOPE("Draw ClientEntity");
      DrawEntity(e, viewport_bounds, screen_center, render_state);
    });
  });
}

void ClientEntitySystem::DrawEntity(NullOptPtr<ClientEntity> entity, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state)
{
  if (entity->m_CustomDraw)
  {
    entity->m_CustomDraw(viewport_bounds, screen_center, render_state);
  }
  else
  {
    DefaultDrawEntity(entity, viewport_bounds, screen_center, render_state, g_ShaderManager.GetDefaultWorldSpaceShader());
  }
}

void ClientEntitySystem::DefaultDrawEntity(NullOptPtr<ClientEntity> entity, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, ShaderProgram & shader)
{
  auto position = entity->GetPosition();
  if (entity->m_PrevPosition)
  {
    position = glm::mix(position, entity->m_PrevPosition.Value(), render_state.GetFramePct());
  }

  DefaultDrawEntity(entity->GetSprite(), position, entity->GetRenderState(), viewport_bounds, screen_center, render_state, shader);
}

void ClientEntitySystem::DefaultDrawEntity(SpritePtr & sprite, const Vector2f & pos, const EntityRenderState & entity_render_state, 
                                     const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, ShaderProgram & shader)
{
  SpriteEngineData::RenderSprite(sprite, render_state, entity_render_state.m_AnimIndex, entity_render_state.m_AnimFrame,
    entity_render_state.m_SkinNameHash, pos - screen_center, entity_render_state.m_Matrix, entity_render_state.m_Color, shader);
}
