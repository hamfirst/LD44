#pragma once

#include "MapEditorClientEntityManager.h"
#include "DocumentListValueWatcher.h"

class MapEditorClientEntityLayerManager
{
public:
  MapEditorClientEntityLayerManager(NotNullPtr<MapEditor> editor, MapDef & map);
  ~MapEditorClientEntityLayerManager();

  NullOptPtr<MapEditorClientEntityManager> GetLayerManager(int layer_index);

protected:
  void Resync();
  void HandleListChange(const ReflectionChangeNotification & change);

private:
  NotNullPtr<MapEditor> m_Editor;

  MapDef & m_Map;

  SparseList<std::unique_ptr<MapEditorClientEntityManager>> m_EntityManagers;
  DocumentListValueWatcher m_Watcher;
};

