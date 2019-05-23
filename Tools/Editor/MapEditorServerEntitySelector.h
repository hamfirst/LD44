#pragma once

#include <QWidget>
#include <QPushButton>
#include <QImage>

#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/ServerEntity/ServerEntityResource.h"
#include "Runtime/ClientEntity/ClientEntityResource.h"

#include "DocumentValueWatcher.h"

class MapEditor;

class MapEditorServerEntitySelector : public QWidget
{
  Q_OBJECT;
public:
  MapEditorServerEntitySelector(NotNullPtr<MapEditor> editor, MapDef & map, QWidget * parent = nullptr);
  ~MapEditorServerEntitySelector();

  void Clear();

  void SetLayer(int layer_index);
  void SetSelectedServerEntity(czstr entity_file);

protected:

  void LoadEntity();

protected:

  virtual void paintEvent(QPaintEvent * ev) override;
  virtual void resizeEvent(QResizeEvent * ev) override;

public slots:

  void pickServerEntity();

private:
  NotNullPtr<MapEditor> m_Editor;
  MapDef & m_Map;

  int m_LayerIndex;

  std::unique_ptr<QPushButton> m_PickServerEntity;

  std::string m_ServerEntityFile;
  ServerEntityLoadLink m_ServerEntity;
  EntityLoadLink m_Entity;
};


