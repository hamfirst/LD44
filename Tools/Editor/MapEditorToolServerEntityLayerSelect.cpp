
#include "MapEditorToolServerEntityLayerSelect.h"
#include "MapEditorToolServerEntityLayerDraw.h"
#include "MapEditor.h"

MapEditorToolServerEntityLayerSelect::MapEditorToolServerEntityLayerSelect(MapEditor & map_editor, int layer_index) :
  MapEditorToolBase(map_editor),
  m_LayerIndex(layer_index)
{

}

void MapEditorToolServerEntityLayerSelect::Init()
{
  m_MapEditor.GetSelector().GetServerObjectSelector()->Clear();
}

void MapEditorToolServerEntityLayerSelect::Cleanup()
{
  auto layer = m_MapEditor.GetServerEntityManager().GetLayerManager(m_LayerIndex);
  if (layer)
  {
    layer->ClearSelection();
  }

  m_MapEditor.GetViewer().ClearSelectionBox();
}

void MapEditorToolServerEntityLayerSelect::Delete()
{
  auto layer = m_MapEditor.GetServerEntityManager().GetLayerManager(m_LayerIndex);
  if (layer != nullptr)
  {
    layer->DeleteSelectedEntities();
  }
}

bool MapEditorToolServerEntityLayerSelect::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto layer = m_MapEditor.GetServerEntityManager().GetLayerManager(m_LayerIndex);
  if (layer == nullptr)
  {
    return false;
  }

  if (alt)
  {
    auto server_object = layer->FindServerEntity(pos);
    if (server_object)
    {
      m_MapEditor.SetSelectedServerEntity(m_LayerIndex, server_object->data());
    }

    return false;
  }

  m_Start = pos;
  if (layer->IsOnSelectedServerEntity(pos))
  {
    m_MapEditor.GetViewer().SnapToGrid(m_Start);
    m_MoveMode = true;
  }
  else
  {
    m_MoveMode = false;
    DrawMove(pos, alt, shift, ctrl);
  }

  return true;
}


void MapEditorToolServerEntityLayerSelect::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  if (m_MoveMode)
  {
    auto snapped_pos = pos;
    m_MapEditor.GetViewer().SnapToGrid(snapped_pos);

    auto layer = m_MapEditor.GetServerEntityManager().GetLayerManager(m_LayerIndex);
    if (layer != nullptr)
    {
      layer->MoveSelection(snapped_pos - m_Start);
    }
  }
  else
  {
    auto selection_box = Box::FromPoints(m_Start, pos);

    auto layer = m_MapEditor.GetServerEntityManager().GetLayerManager(m_LayerIndex);
    if (layer != nullptr)
    {
      layer->SelectServerEntities(selection_box);
    }

    m_MapEditor.GetViewer().SetSelectionBox(selection_box);
  }
}

void MapEditorToolServerEntityLayerSelect::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  if (m_MoveMode)
  {
    auto layer = m_MapEditor.GetServerEntityManager().GetLayerManager(m_LayerIndex);
    if (layer != nullptr)
    {
      layer->DropSelection();
    }
  }
  else
  {
    m_MapEditor.GetViewer().ClearSelectionBox();

    auto layer = m_MapEditor.GetServerEntityManager().GetLayerManager(m_LayerIndex);
    if (layer != nullptr)
    {
      auto sel_index = layer->GetSingleSelectionIndex();
      if (sel_index)
      {
        MapEditorLayerSelection layer_selection;
        layer_selection.m_Type = MapEditorLayerItemType::kServerEntity;
        layer_selection.m_Index = (std::size_t)m_LayerIndex;
        layer_selection.m_SubIndex = sel_index.Value();
        m_MapEditor.ChangeLayerSelection(layer_selection, false);
      }
      else
      {
        m_MapEditor.ClearPropertyPanel();
      }
    }
  }
}

void MapEditorToolServerEntityLayerSelect::DrawCancel()
{
  auto layer = m_MapEditor.GetServerEntityManager().GetLayerManager(m_LayerIndex);
  if (layer != nullptr)
  {
    if (m_MoveMode)
    {
      layer->MoveSelection(Vector2(0, 0));
    }

    layer->ClearSelection();
  }

  m_MapEditor.GetViewer().ClearSelectionBox();
}
