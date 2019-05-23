
#include "MapEditorToolClientEntityLayerDraw.h"
#include "MapEditorToolClientEntityLayerSelect.h"
#include "MapEditor.h"

MapEditorToolClientEntityLayerDraw::MapEditorToolClientEntityLayerDraw(MapEditor & map_editor, int layer_index, czstr entity_file) :
  MapEditorToolBase(map_editor),
  m_LayerIndex(layer_index),
  m_EntityFile(entity_file)
{

}

void MapEditorToolClientEntityLayerDraw::Init()
{
  auto layer = m_MapEditor.GetClientEntityManager().GetLayerManager(m_LayerIndex);
  if (layer)
  {
    layer->SetPreviewEntity(m_EntityFile.data());
  }
}

void MapEditorToolClientEntityLayerDraw::Cleanup()
{
  auto layer = m_MapEditor.GetClientEntityManager().GetLayerManager(m_LayerIndex);
  if (layer)
  {
    layer->ClearPreviewEntity();
  }
}

void MapEditorToolClientEntityLayerDraw::RightClick()
{
  m_MapEditor.GetViewer().SetTool(MapEditorTool<MapEditorToolClientEntityLayerSelect>{}, m_LayerIndex);
}

void MapEditorToolClientEntityLayerDraw::DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto layer = m_MapEditor.GetClientEntityManager().GetLayerManager(m_LayerIndex);
  if (layer == nullptr)
  {
    return;
  }

  auto snapped_pos = pos;
  m_MapEditor.GetViewer().SnapToGrid(snapped_pos);
  layer->SetPreviewEntityPosition(snapped_pos);
}

bool MapEditorToolClientEntityLayerDraw::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto layer = m_MapEditor.GetClientEntityManager().GetLayerManager(m_LayerIndex);
  if (layer == nullptr)
  {
    return false;
  }

  layer->CommitPreviewEntity();
  return true;
}
