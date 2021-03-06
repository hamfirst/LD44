#pragma once

#include <QWidget>
#include <QPushButton>
#include <QImage>

#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/ClientEntity/ClientEntityResource.h"

#include "DocumentValueWatcher.h"

class MapEditor;

class MapEditorClientEntitySelector : public QWidget
{
  Q_OBJECT;
public:
  MapEditorClientEntitySelector(NotNullPtr<MapEditor> editor, MapDef & map, QWidget * parent = nullptr);
  ~MapEditorClientEntitySelector();

  void Clear();

  void SetLayer(int layer_index);
  void SetSelectedEntity(czstr entity_file);

protected:

  virtual void paintEvent(QPaintEvent * ev) override;
  virtual void resizeEvent(QResizeEvent * ev) override;

public slots:

  void pickEntity();

private:
  NotNullPtr<MapEditor> m_Editor;
  MapDef & m_Map;

  int m_LayerIndex;

  std::unique_ptr<QPushButton> m_PickEntity;

  std::string m_EntityFile;
  EntityLoadLink m_Entity;
};


