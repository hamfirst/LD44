
#include <QPainter>

#include "Engine/Sprite/SpriteEngineData.h"

#include "Runtime/ServerEntity/ServerEntitySystem.h"

#include "MapEditorServerEntitySelector.h"
#include "MapEditor.h"

MapEditorServerEntitySelector::MapEditorServerEntitySelector(NotNullPtr<MapEditor> editor, MapDef & map, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_Map(map),
  m_LayerIndex(-1),
  m_PickServerEntity(std::make_unique<QPushButton>("Pick Server Entity File...", this))
{
  connect(m_PickServerEntity.get(), &QPushButton::pressed, this, &MapEditorServerEntitySelector::pickServerEntity);
}

MapEditorServerEntitySelector::~MapEditorServerEntitySelector()
{

}

void MapEditorServerEntitySelector::Clear()
{
  m_ServerEntityFile.clear();
  m_ServerEntity = {};
}

void MapEditorServerEntitySelector::SetLayer(int layer_index)
{
  m_LayerIndex = layer_index;
}

void MapEditorServerEntitySelector::SetSelectedServerEntity(czstr server_entity_file)
{
  m_ServerEntityFile = server_entity_file;
  ServerEntityResource::LoadWithCallback(server_entity_file, [this](NotNullPtr<ServerEntityResource>) { LoadEntity(); repaint(); }, m_ServerEntity);
}

void MapEditorServerEntitySelector::LoadEntity()
{
  auto data = m_ServerEntity.GetData();
  auto init_data_type_name_hash = data->m_InitData.GetTypeNameHash();
  
  auto entity_file = g_ServerEntitySystem.GetEntityBindingForInitDataTypeNameHash(init_data_type_name_hash);
  if (entity_file)
  {
    ClientEntityResource::LoadWithCallback(entity_file, [this](NotNullPtr<ClientEntityResource>){ repaint(); }, m_Entity);
  }
  else
  {
    m_Entity.Clear();
  }
}

void MapEditorServerEntitySelector::paintEvent(QPaintEvent * ev)
{
  QPainter p(this);

  p.drawText(300, 13, m_ServerEntityFile.data());

  auto server_entity_resource = m_ServerEntity.GetResource();
  if (server_entity_resource)
  {
    auto entity_resource = m_Entity.GetResource();
    if (entity_resource)
    {
      auto & sprite = entity_resource->GetSprite();

      Box tex_coords;
      auto texture = SpriteEngineData::GetSpriteFrame(sprite, 0, 0, tex_coords);

      if (texture)
      {
        auto pixel_buffer = texture->GetPixelBuffer();

        QImage::Format img_format;
        switch (pixel_buffer->GetPixelSize())
        {
        case 3:
          img_format = QImage::Format_RGB888;
          break;
        case 4:
          img_format = QImage::Format_RGBA8888;
          break;
        default:
          return;
        }

        QImage img(pixel_buffer->GetPixelBuffer(), pixel_buffer->GetWidth(), pixel_buffer->GetHeight(), img_format);

        auto texture_size = tex_coords.Size();
        p.drawImage(QRect(300, 20, texture_size.x * 2, texture_size.y * 2), img, QRect(tex_coords.m_Start.x, tex_coords.m_Start.y, texture_size.x, texture_size.y));
      }
    }
  }
}

void MapEditorServerEntitySelector::resizeEvent(QResizeEvent * ev)
{
  m_PickServerEntity->setGeometry(0, 0, 300, height());
}

void MapEditorServerEntitySelector::pickServerEntity()
{
  auto file_name = m_Editor->GetFileNameForAssetType("svrent");
  if (file_name)
  {
    m_Editor->SetSelectedServerEntity(m_LayerIndex, file_name->data());
  }
}
