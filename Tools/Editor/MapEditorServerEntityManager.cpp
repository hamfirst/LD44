
#include "Foundation/FileSystem/Path.h"

#include "Engine/Shader/ShaderManager.h"
#include "Engine/Sprite/SpriteEngineData.h"

#include "Runtime/Map/MapDef.refl.meta.h"
#include "Runtime/ServerEntity/ServerEntitySystem.h"

#include "StormData/StormDataJson.h"

#include "MapEditorServerEntityManager.h"
#include "MapEditor.h"


MapEditorServerEntityManager::MapEditorServerEntityManager(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index) :
  m_Editor(editor),
  m_Map(map),
  m_LayerIndex(layer_index),
  m_SpriteMirror(editor),
  m_Hidden(false),
  m_Collapsed(false)
{
  m_GetSprite = CreateMirrorList<RMergeList, MapServerEntity, ServerEntityInitDataPolyType, MapEditorServerEntityManagerElement, MapEditorServerEntityManager>(
    m_SpriteMirror,
    m_Map.m_ServerEntityLayers[layer_index].m_Entities,
    [this]() -> void * { auto layer = m_Map.m_ServerEntityLayers.TryGet(m_LayerIndex); return layer ? &layer->m_Entities : nullptr; },
    ".m_ServerEntity.m_InitData",
    [](MapServerEntity & elem, NotNullPtr<MapEditorServerEntityManager>) -> ServerEntityInitDataPolyType & { return elem.m_ServerEntity.m_InitData; },
    [](ServerEntityInitDataPolyType & init_data, MapEditorServerEntityManagerElement & elem, std::size_t index, NotNullPtr<MapEditorServerEntityManager> ptr) {},
    [](ServerEntityInitDataPolyType & init_data, MapEditorServerEntityManagerElement & elem, std::size_t index, NotNullPtr<MapEditorServerEntityManager> ptr)
    {
      auto entity_file = g_ServerEntitySystem.GetEntityBindingForInitDataTypeNameHash(init_data.GetTypeNameHash());
      if (entity_file != nullptr)
      {
        elem.m_Entity = ClientEntityResource::Load(entity_file);
      }
      else
      {
        elem.m_Entity.Clear();
      }
    }, this);
}

void MapEditorServerEntityManager::AddServerEntity(czstr entity_file, const Vector2 & pos)
{
  m_Editor->BeginTransaction();

  auto new_index = m_Map.m_ServerEntityLayers[m_LayerIndex].m_Entities.HighestIndex() + 1;
  auto & server_entity = m_Map.m_ServerEntityLayers[m_LayerIndex].m_Entities.EmplaceBack();
  server_entity.m_Name = GetFileStemForCanonicalPath(entity_file);
  server_entity.m_GUID = GetRandomNumber();
  server_entity.m_XPosition = pos.x;
  server_entity.m_YPosition = pos.y;

  std::string link_dst_path = ".m_ServerEntityLayers[" + std::to_string(m_LayerIndex) + "].m_Entities[" + std::to_string(new_index) + "].m_ServerEntity";
  m_Editor->CreateLink(entity_file, "", link_dst_path.data());

  m_Editor->CommitChanges();
}

void MapEditorServerEntityManager::RemoveServerEntity(std::size_t index)
{
  ClearSelection();

  m_Editor->BeginTransaction();
  std::string link_dst_path = ".m_ServerEntityLayers[" + std::to_string(m_LayerIndex) + "].m_Entities[" + std::to_string(index) + "].m_ServerEntity";

  m_Map.m_ServerEntityLayers[m_LayerIndex].m_Entities.RemoveAt(index);
  m_Editor->CommitChanges();
}

void MapEditorServerEntityManager::SetPreviewServerEntity(czstr server_entity_file)
{
  m_PreviewServerEntityFile = server_entity_file;
  m_PreviewServerEntityPosition.Clear();
  m_PreviewEntity.Clear();

  ServerEntityResource::LoadWithCallback(server_entity_file, [this](NotNullPtr<ServerEntityResource> resource) {
    auto init_data_type_name_hash = resource->GetData()->m_InitData.GetTypeNameHash();
    auto entity_file = g_ServerEntitySystem.GetEntityBindingForInitDataTypeNameHash(init_data_type_name_hash);
    if (entity_file)
    {
      m_PreviewEntity = ClientEntityResource::Load(entity_file);
    }
    else
    {
      m_PreviewEntity.Clear();
    }
  }, m_PreviewServerEntity);
}

void MapEditorServerEntityManager::SetPreviewServerEntityPosition(const Vector2 & pos)
{
  m_PreviewServerEntityPosition = pos;
}

void MapEditorServerEntityManager::ClearPreviewServerEntity()
{
  m_PreviewServerEntity.Clear();
  m_PreviewServerEntityPosition.Clear();
  m_PreviewEntity.Clear();
}

void MapEditorServerEntityManager::CommitPreviewServerEntity()
{
  if (m_PreviewServerEntity.GetResource() == nullptr || m_PreviewServerEntityPosition == false)
  {
    return;
  }

  AddServerEntity(m_PreviewServerEntityFile.data(), m_PreviewServerEntityPosition.Value());
}

void MapEditorServerEntityManager::SelectServerEntities(const Box & box)
{
  ClearSelection();
  m_SelectedServerEntityOffset = {};

  for (auto elem : m_Map.m_ServerEntityLayers[m_LayerIndex].m_Entities)
  {
    auto data = m_GetSprite(elem.first);

    if (data->m_Frame && BoxIntersect(box, data->m_Frame.Value()))
    {
      m_SelectedServerEntities.push_back(elem.first);
    }
  }
}

Optional<std::string> MapEditorServerEntityManager::FindServerEntity(const Vector2 & pos)
{
  for (auto elem : m_Map.m_ServerEntityLayers[m_LayerIndex].m_Entities)
  {
    auto data = m_GetSprite(elem.first);

    if (data->m_Frame && PointInBox(data->m_Frame.Value(), pos))
    {
      auto links = m_Editor->GetLinks();
      auto test_path = std::string(".m_ServerEntityLayers[") + std::to_string(m_LayerIndex) + "].m_Entities[" + std::to_string(elem.first) + "].m_ServerEntity";

      for (auto & link : links)
      {
        if (link.m_LocalPath == test_path)
        {
          return link.m_SourceAsset;
        }
      }

      return{};
    }
  }

  return{};
}

void MapEditorServerEntityManager::DropSelection()
{
  if (m_SelectedServerEntities.size() == 0)
  {
    return;
  }

  if (m_SelectedServerEntityOffset.x != 0 || m_SelectedServerEntityOffset.y != 0)
  {
    m_Editor->BeginTransaction();
    for (auto elem : m_Map.m_ServerEntityLayers[m_LayerIndex].m_Entities)
    {
      if (vfind(m_SelectedServerEntities, elem.first))
      {
        elem.second.m_XPosition += m_SelectedServerEntityOffset.x;
        elem.second.m_YPosition += m_SelectedServerEntityOffset.y;
      }
    }

    m_Editor->CommitChanges();
  }

  m_SelectedServerEntityOffset = {};
}

void MapEditorServerEntityManager::ClearSelection()
{
  DropSelection();

  m_SelectedServerEntities.clear();
}

void MapEditorServerEntityManager::DeselectServerEntities()
{
  m_SelectedServerEntities.clear();
  for (auto elem : m_Map.m_ServerEntityLayers[m_LayerIndex].m_Entities)
  {
    if (vfind(m_SelectedServerEntities, elem.first))
    {
      elem.second.m_XPosition += m_SelectedServerEntityOffset.x;
      elem.second.m_YPosition += m_SelectedServerEntityOffset.y;
    }
  }

  m_SelectedServerEntities.clear();
  m_SelectedServerEntityOffset = {};
}

void MapEditorServerEntityManager::DeleteSelectedEntities()
{
  if (m_SelectedServerEntities.size() == 0)
  {
    return;
  }

  m_Editor->BeginTransaction();

  for (auto index : m_SelectedServerEntities)
  {
    m_Map.m_ServerEntityLayers[m_LayerIndex].m_Entities.RemoveAt(index);
  }

  m_SelectedServerEntities.clear();
  m_SelectedServerEntityOffset = {};

  m_Editor->CommitChanges();
}

void MapEditorServerEntityManager::MoveSelection(const Vector2 & offset)
{
  m_SelectedServerEntityOffset = offset;
}

bool MapEditorServerEntityManager::IsOnSelectedServerEntity(const Vector2 & pos)
{
  for (auto selection : m_SelectedServerEntities)
  {
    if (m_Map.m_ServerEntityLayers[m_LayerIndex].m_Entities.HasAt(selection) == false)
    {
      continue;
    }

    auto & ServerEntity = m_Map.m_ServerEntityLayers[m_LayerIndex].m_Entities[selection];
    auto data = m_GetSprite(selection);

    if (data == nullptr || data->m_Frame == false)
    {
      continue;
    }

    auto frame = data->m_Frame.Value();
    if (PointInBox(frame, pos))
    {
      return true;
    }
  }

  return false;
}

void MapEditorServerEntityManager::SetSingleSelection(std::size_t entity_index)
{
  ClearSelection();
  m_SelectedServerEntities.push_back(entity_index);
}

Optional<std::size_t> MapEditorServerEntityManager::GetSingleSelectionIndex()
{
  if (m_SelectedServerEntities.size() != 1)
  {
    return{};
  }

  if (m_Map.m_ServerEntityLayers[m_LayerIndex].m_Entities.HasAt(m_SelectedServerEntities[0]) == false)
  {
    return{};
  }

  return m_SelectedServerEntities[0];
}

void MapEditorServerEntityManager::Draw(const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state)
{
  for (auto elem : m_Map.m_ServerEntityLayers[m_LayerIndex].m_Entities)
  {
    auto data = m_GetSprite(elem.first);
    auto entity = data->m_Entity.GetResource();

    if (entity)
    {
      auto & sprite = entity->GetSprite();

      Box tex_coords;
      if (SpriteEngineData::GetSpriteFrame(sprite, 0, 0, tex_coords))
      {
        auto pos = Vector2(elem.second.m_XPosition, elem.second.m_YPosition);
        auto frame_size = tex_coords.Size();
        Box frame = Box::FromFrameCenterAndSize(pos, frame_size);

        if (vfind(m_SelectedServerEntities, elem.first))
        {
          frame.m_Start += m_SelectedServerEntityOffset;
          frame.m_End += m_SelectedServerEntityOffset;
          pos += m_SelectedServerEntityOffset;
        }

        data->m_Frame = frame;

        if (BoxIntersect(viewport_bounds, frame))
        {
          RenderVec2 draw_pos = pos;
          draw_pos -= screen_center;

          SpriteEngineData::RenderSprite(sprite, render_state, 0, 0, kSpriteDefaultSkin, draw_pos);
        }
      }
    }
  }
}

void MapEditorServerEntityManager::DrawPreviewServerEntity(const RenderVec2 & screen_center, RenderState & render_state)
{
  auto entity = m_PreviewEntity.GetResource();
  if (entity == nullptr || entity->IsLoaded() == false || m_PreviewServerEntityPosition == false)
  {
    return;
  }

  auto & sprite = entity->GetSprite();

  RenderVec2 draw_pos = RenderVec2{ m_PreviewServerEntityPosition.Value() };
  draw_pos -= screen_center;

  SpriteEngineData::RenderSprite(sprite, render_state, 0, 0, kSpriteDefaultSkin, draw_pos, RenderVec4{ 1, 0, 0, 1 }, Color(255, 255, 255, 160));
}

void MapEditorServerEntityManager::DrawSelection(VertexBuffer & vertex_buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state)
{
  if (m_SelectedServerEntities.size() == 0)
  {
    return;
  }

  LineVertexBufferBuilder line_builder;
  QuadVertexBuilderInfo quad;

  for (auto selection : m_SelectedServerEntities)
  {
    if (m_Map.m_ServerEntityLayers[m_LayerIndex].m_Entities.HasAt(selection) == false)
    {
      continue;
    }

    auto & ServerEntity = m_Map.m_ServerEntityLayers[m_LayerIndex].m_Entities[selection];
    auto data = m_GetSprite(selection);

    if (data == nullptr || data->m_Frame == false)
    {
      continue;
    }

    auto frame = data->m_Frame.Value();
    if (BoxIntersect(viewport_bounds, frame))
    {
      quad.m_Position = frame;
      quad.m_TexCoords = Box::FromPoint({});
      quad.m_TextureSize = Vector2(1, 1);
      quad.m_Color = Color(255, 255, 255, 255);

      line_builder.AddBox(quad);
    }
  }

  line_builder.FillVertexBuffer(vertex_buffer);
  auto & shader = g_ShaderManager.GetDefaultWorldSpaceShader();
  render_state.BindShader(shader);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), -screen_center);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1, 0, 1, 1 });

  render_state.BindTexture(render_state.GetDefaultTexture());
  render_state.BindVertexBuffer(vertex_buffer);
  render_state.Draw();
}

void MapEditorServerEntityManager::ToggleHidden()
{
  m_Hidden = !m_Hidden;
}

void MapEditorServerEntityManager::SetHidden(bool hidden)
{
  m_Hidden = hidden;
}

bool MapEditorServerEntityManager::IsHidden()
{
  return m_Hidden;
}

void MapEditorServerEntityManager::ToggleColapsed()
{
  m_Collapsed = !m_Collapsed;
}

bool MapEditorServerEntityManager::IsCollapsed()
{
  return m_Collapsed;
}
