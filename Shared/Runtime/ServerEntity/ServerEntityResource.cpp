
#include "Runtime/RuntimeCommon.h"
#include "Runtime/ServerEntity/ServerEntityResource.h"
#include "Runtime/ServerEntity/ServerEntityDef.refl.meta.h"

#include "StormData/StormDataJson.h"

#include <sb/vector.h>

ServerEntityResource::ServerEntityResource(Any && load_data, uint32_t path_hash, czstr path) :
  DocumentResourceBase(std::move(load_data), path_hash, path)
{

}

NotNullPtr<ServerEntityDef> ServerEntityResource::GetData()
{
  return &m_Data;
}

ServerEntityLoadLink ServerEntityResource::AddLoadCallback(Delegate<void, NotNullPtr<ServerEntityResource>> && callback)
{
  if (m_Loaded)
  {
    callback(this);
  }

  return DocumentResourceLoadCallbackLink<ServerEntityDef, ServerEntityResource>(
    DocumentResourceReference<ServerEntityResource>(this), m_LoadCallbacks.AddDelegate(std::move(callback)));
}

void ServerEntityResource::AddLoadCallback(Delegate<void, NotNullPtr<ServerEntityResource>> && callback, ServerEntityLoadLink & link)
{
  link = DocumentResourceLoadCallbackLink<ServerEntityDef, ServerEntityResource>(
    DocumentResourceReference<ServerEntityResource>(this), m_LoadCallbacks.AddDelegate(callback));

  if (m_Loaded)
  {
    callback(this);
  }
}

ServerEntityResourcePtr ServerEntityResource::Find(uint32_t file_path_hash)
{
  auto resource = FindDocumentResource(file_path_hash);
  if (resource)
  {
    auto p_this = static_cast<ServerEntityResource *>(resource);
    return ServerEntityResourcePtr(DocumentResourceReference<ServerEntityResource>(p_this));
  }

  return {};
}

ServerEntityResourcePtr ServerEntityResource::Load(czstr file_path)
{
  auto resource = LoadDocumentResource(file_path, [](Any && load_data, uint32_t path_hash, czstr path) -> std::unique_ptr<DocumentResourceBase>
          { return std::make_unique<ServerEntityResource>(std::move(load_data), path_hash, path); });
  auto p_this = static_cast<ServerEntityResource *>(resource);
  return ServerEntityResourcePtr(DocumentResourceReference<ServerEntityResource>(p_this));
}

ServerEntityLoadLink ServerEntityResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<ServerEntityResource>> && callback)
{
  auto resource = LoadDocumentResource(file_path, [](Any && load_data, uint32_t path_hash, czstr path) -> std::unique_ptr<DocumentResourceBase>
          { return std::make_unique<ServerEntityResource>(std::move(load_data), path_hash, path); });
  auto p_this = static_cast<ServerEntityResource *>(resource);

  return p_this->AddLoadCallback(std::move(callback));
}

void ServerEntityResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<ServerEntityResource>> && callback, ServerEntityLoadLink & link)
{
  auto resource = LoadDocumentResource(file_path, [](Any && load_data, uint32_t path_hash, czstr path) -> std::unique_ptr<DocumentResourceBase>
          { return std::make_unique<ServerEntityResource>(std::move(load_data), path_hash, path); });
  auto p_this = static_cast<ServerEntityResource *>(resource);

  p_this->AddLoadCallback(std::move(callback), link);
}

void ServerEntityResource::OnDataLoadComplete(const std::string & resource_data)
{
  StormReflParseJson(m_Data, resource_data.data());
  m_Loaded = true;
}

void ServerEntityResource::CallAssetLoadCallbacks()
{
  m_LoadCallbacks.Call(this);
}

