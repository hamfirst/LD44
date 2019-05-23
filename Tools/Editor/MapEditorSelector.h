#pragma once

#include <QWidget>

#include "MapEditorTileSelector.h"
#include "MapEditorClientEntitySelector.h"
#include "MapEditorServerEntitySelector.h"
#include "MapEditorParallaxObjectSelector.h"

class MapEditorSelector : public QWidget
{
  Q_OBJECT;
public:
  MapEditorSelector(NotNullPtr<MapEditor> editor, MapDef & map, QWidget * parent = nullptr);

  NotNullPtr<MapEditorTileSelector> GetTileSelector();
  NotNullPtr<MapEditorClientEntitySelector> GetEntitySelector();
  NotNullPtr<MapEditorServerEntitySelector> GetServerObjectSelector();
  NotNullPtr<MapEditorParallaxObjectSelector> GetParallaxObjectSelector();

protected:

  void resizeEvent(QResizeEvent * ev);

private:

  std::unique_ptr<MapEditorTileSelector> m_TileSelector;
  std::unique_ptr<MapEditorClientEntitySelector> m_EntitySelector;
  std::unique_ptr<MapEditorServerEntitySelector> m_ServerObjectSelector;
  std::unique_ptr<MapEditorParallaxObjectSelector> m_ParallaxObjectSelector;
};


