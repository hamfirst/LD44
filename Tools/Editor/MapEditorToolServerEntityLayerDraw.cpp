
#include "MapEditorToolServerEntityLayerDraw.h"
#include "MapEditorToolServerEntityLayerSelect.h"
#include "MapEditor.h"

MapEditorToolServerEntityLayerDraw::MapEditorToolServerEntityLayerDraw(MapEditor & map_editor, int layer_index, czstr entity_file) :
  MapEditorToolBase(map_editor),
  m_LayerIndex(layer_index),
  m_ServerObjectFile(entity_file)
{

}

void MapEditorToolServerEntityLayerDraw::Init()
{
  auto layer = m_MapEditor.GetServerEntityManager().GetLayerManager(m_LayerIndex);
  if (layer)
  {
    layer->SetPreviewServerEntity(m_ServerObjectFile.data());
  }
}

void MapEditorToolServerEntityLayerDraw::Cleanup()
{
  auto layer = m_MapEditor.GetServerEntityManager().GetLayerManager(m_LayerIndex);
  if (layer)
  {
    layer->ClearPreviewServerEntity();
  }
}

void MapEditorToolServerEntityLayerDraw::RightClick()
{
  m_MapEditor.GetViewer().SetTool(MapEditorTool<MapEditorToolServerEntityLayerSelect>{}, m_LayerIndex);
}

void MapEditorToolServerEntityLayerDraw::DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto layer = m_MapEditor.GetServerEntityManager().GetLayerManager(m_LayerIndex);
  if (layer == nullptr)
  {
    return;
  }

  auto snapped_pos = pos;
  m_MapEditor.GetViewer().SnapToGrid(snapped_pos);
  layer->SetPreviewServerEntityPosition(snapped_pos);
}

bool MapEditorToolServerEntityLayerDraw::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto layer = m_MapEditor.GetServerEntityManager().GetLayerManager(m_LayerIndex);
  if (layer == nullptr)
  {
    return false;
  }

  layer->CommitPreviewServerEntity();
  return true;
}
