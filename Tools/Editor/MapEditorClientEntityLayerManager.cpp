
#include "MapEditorClientEntityLayerManager.h"
#include "MapEditor.h"

MapEditorClientEntityLayerManager::MapEditorClientEntityLayerManager(NotNullPtr<MapEditor> editor, MapDef & map) :
  m_Editor(editor),
  m_Map(map),
  m_Watcher(m_Editor)
{
  m_Watcher.SetPath(".m_ClientEntityLayers", false, false, [] {return true; });
  m_Watcher.SetChangeCallback([=](const ReflectionChangeNotification & change) { HandleListChange(change); });

  Resync();
}

MapEditorClientEntityLayerManager::~MapEditorClientEntityLayerManager()
{

}

NullOptPtr<MapEditorClientEntityManager> MapEditorClientEntityLayerManager::GetLayerManager(int layer_index)
{
  if (m_EntityManagers.HasAt((std::size_t)layer_index) == false)
  {
    return nullptr;
  }

  return m_EntityManagers[layer_index].get();
}

void MapEditorClientEntityLayerManager::Resync()
{
  SparseList<std::unique_ptr<MapEditorClientEntityManager>> old_layers = std::move(m_EntityManagers);

  for (auto elem : m_Map.m_ClientEntityLayers)
  {
    m_EntityManagers.EmplaceAt(elem.first, std::make_unique<MapEditorClientEntityManager>(m_Editor, m_Map, (int)elem.first));
  }
}

void MapEditorClientEntityLayerManager::HandleListChange(const ReflectionChangeNotification & change)
{
  if (change.m_Type == ReflectionNotifyChangeType::kInsert)
  {
    if (m_Map.m_ClientEntityLayers.HasAt(change.m_SubIndex))
    {
      m_EntityManagers.EmplaceAt(change.m_SubIndex, std::make_unique<MapEditorClientEntityManager>(m_Editor, m_Map, (int)change.m_SubIndex));
    }
  }
  else if (change.m_Type == ReflectionNotifyChangeType::kRemove)
  {
    m_EntityManagers.RemoveAt(change.m_SubIndex);
  }
  else
  {
    Resync();
  }
}
