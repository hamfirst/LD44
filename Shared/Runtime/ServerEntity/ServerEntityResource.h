#pragma once

#include "Foundation/Delegate/DelegateList.h"

#include "Runtime/DocumentResource/DocumentResourceBase.h"
#include "Runtime/DocumentResource/DocumentResourcePtr.h"
#include "Runtime/ServerEntity/ServerEntityDef.refl.h"
#include "Runtime/Sprite/SpriteResource.h"

class ServerEntityResource;

using ServerEntityResourcePtr = DocumentResourcePtr<ServerEntityDef, ServerEntityResource>;
using ServerEntityLoadLink = DocumentResourceLoadCallbackLink<ServerEntityDef, ServerEntityResource>;

class ServerEntityResource : public DocumentResourceBase
{
public:
  ServerEntityResource(Any && load_data, uint32_t path_hash, czstr path);

  NotNullPtr<ServerEntityDef> GetData();
  ServerEntityLoadLink AddLoadCallback(Delegate<void, NotNullPtr<ServerEntityResource>> && callback);
  void AddLoadCallback(Delegate<void, NotNullPtr<ServerEntityResource>> && callback, ServerEntityLoadLink & link);

  static ServerEntityResourcePtr Find(uint32_t file_path_hash);
  static ServerEntityResourcePtr Load(czstr file_path);
  static ServerEntityLoadLink LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<ServerEntityResource>> && callback);
  static void LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<ServerEntityResource>> && callback, ServerEntityLoadLink & link);

protected:
  virtual void OnDataLoadComplete(const std::string & resource_data) override;
  virtual void CallAssetLoadCallbacks() override;

private:

  ServerEntityDef m_Data;
  DelegateList<void, NotNullPtr<ServerEntityResource>> m_LoadCallbacks;
};
