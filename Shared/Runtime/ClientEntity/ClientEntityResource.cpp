
#include "Runtime/RuntimeCommon.h"
#include "Runtime/ClientEntity/ClientEntityResource.h"
#include "Runtime/ClientEntity/ClientEntityDef.refl.meta.h"

#include "StormData/StormDataJson.h"

#include <sb/vector.h>

ClientEntityResource::ClientEntityResource(Any && load_data, uint32_t path_hash, czstr path) :
  DocumentResourceBase(std::move(load_data), path_hash, path)
{

}

NotNullPtr<ClientEntityDef> ClientEntityResource::GetData()
{
  return &m_Data;
}

EntityLoadLink ClientEntityResource::AddLoadCallback(Delegate<void, NotNullPtr<ClientEntityResource>> && callback)
{
  if (m_Loaded)
  {
    callback(this);
  }

  return DocumentResourceLoadCallbackLink<ClientEntityDef, ClientEntityResource>(
    DocumentResourceReference<ClientEntityResource>(this), m_LoadCallbacks.AddDelegate(std::move(callback)));
}

void ClientEntityResource::AddLoadCallback(Delegate<void, NotNullPtr<ClientEntityResource>> && callback, EntityLoadLink & link)
{
  link = DocumentResourceLoadCallbackLink<ClientEntityDef, ClientEntityResource>(
    DocumentResourceReference<ClientEntityResource>(this), m_LoadCallbacks.AddDelegate(callback));

  if (m_Loaded)
  {
    callback(this);
  }
}

ClientEntityResourcePtr ClientEntityResource::Find(uint32_t file_path_hash)
{
  auto resource = FindDocumentResource(file_path_hash);
  if (resource)
  {
    auto p_this = static_cast<ClientEntityResource *>(resource);
    return ClientEntityResourcePtr(DocumentResourceReference<ClientEntityResource>(p_this));
  }

  return {};
}

ClientEntityResourcePtr ClientEntityResource::Load(czstr file_path)
{
  if(file_path == nullptr || file_path[0] == 0)
  {
    return {};
  }

  auto resource = LoadDocumentResource(file_path, [](Any && load_data, uint32_t path_hash, czstr path) -> std::unique_ptr<DocumentResourceBase>
          { return std::make_unique<ClientEntityResource>(std::move(load_data), path_hash, path); });
  auto p_this = static_cast<ClientEntityResource *>(resource);
  return ClientEntityResourcePtr(DocumentResourceReference<ClientEntityResource>(p_this));
}

EntityLoadLink ClientEntityResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<ClientEntityResource>> && callback)
{
  if(file_path == nullptr || file_path[0] == 0)
  {
    return {};
  }

  auto resource = LoadDocumentResource(file_path, [](Any && load_data, uint32_t path_hash, czstr path) -> std::unique_ptr<DocumentResourceBase>
          { return std::make_unique<ClientEntityResource>(std::move(load_data), path_hash, path); });
  auto p_this = static_cast<ClientEntityResource *>(resource);

  return p_this->AddLoadCallback(std::move(callback));
}

void ClientEntityResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<ClientEntityResource>> && callback, EntityLoadLink & link)
{
  if(file_path == nullptr || file_path[0] == 0)
  {
    return;
  }

  auto resource = LoadDocumentResource(file_path, [](Any && load_data, uint32_t path_hash, czstr path) -> std::unique_ptr<DocumentResourceBase>
          { return std::make_unique<ClientEntityResource>(std::move(load_data), path_hash, path); });
  auto p_this = static_cast<ClientEntityResource *>(resource);

  p_this->AddLoadCallback(std::move(callback), link);
}

SpritePtr & ClientEntityResource::GetSprite()
{
  return m_Sprite;
}

const SpritePtr & ClientEntityResource::GetSprite() const
{
  return m_Sprite;
}

void ClientEntityResource::OnDataLoadComplete(const std::string & resource_data)
{
  StormReflParseJson(m_Data, resource_data.data());

  if (m_Data.m_Sprite.length() > 0)
  {
    m_Sprite = SpriteResource::Load(m_Data.m_Sprite.data());
  }
  else
  {
    m_Sprite = {};
  }

  m_Loaded = true;
}

void ClientEntityResource::CallAssetLoadCallbacks()
{
  m_LoadCallbacks.Call(this);
}

