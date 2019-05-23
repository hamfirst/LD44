#pragma once

#include "Foundation/Common.h"
#include "Foundation/SparseList/SparseList.h"
#include "Foundation/SpatialDatabase/SpatialDatabase.h"
#include "Foundation/Allocator/IdAllocator.h"

#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/ServerEntity/ServerEntityResource.h"
#include "Runtime/ClientEntity/ClientEntityResource.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Rendering/VertexBuffer.h"

#include "DocumentSubValueListMirror.h"

class MapEditor;

struct MapEditorServerEntityManagerElement
{
  ClientEntityResourcePtr m_Entity;
  Optional<Box> m_Frame;
};

class MapEditorServerEntityManager
{
public:
  MapEditorServerEntityManager(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index);

  void AddServerEntity(czstr entity_file, const Vector2 & pos);
  void RemoveServerEntity(std::size_t index);

  void SetPreviewServerEntity(czstr entity_file);
  void SetPreviewServerEntityPosition(const Vector2 & pos);
  void ClearPreviewServerEntity();
  void CommitPreviewServerEntity();

  void SelectServerEntities(const Box & box);
  Optional<std::string> FindServerEntity(const Vector2 & pos);
  void DropSelection();
  void ClearSelection();
  void DeselectServerEntities();
  void DeleteSelectedEntities();
  void MoveSelection(const Vector2 & offset);
  bool IsOnSelectedServerEntity(const Vector2 & pos);

  void SetSingleSelection(std::size_t entity_index);
  Optional<std::size_t> GetSingleSelectionIndex();

  void Draw(const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state);
  void DrawPreviewServerEntity(const RenderVec2 & screen_center, RenderState & render_state);
  void DrawSelection(VertexBuffer & vertex_buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state);

  void ToggleHidden();
  void SetHidden(bool hidden);
  bool IsHidden();

  void ToggleColapsed();
  bool IsCollapsed();

private:
  NotNullPtr<MapEditor> m_Editor;

  MapDef & m_Map;
  int m_LayerIndex;

  Optional<Vector2> m_PreviewServerEntityPosition;
  std::string m_PreviewServerEntityFile;
  ServerEntityLoadLink m_PreviewServerEntity;
  ClientEntityResourcePtr m_PreviewEntity;
  
  std::vector<std::size_t> m_SelectedServerEntities;
  Vector2 m_SelectedServerEntityOffset;
  
  DocumentSubValueListMirror m_SpriteMirror;
  Delegate<NullOptPtr<MapEditorServerEntityManagerElement>, std::size_t> m_GetSprite;

  bool m_Hidden;
  bool m_Collapsed;
};
