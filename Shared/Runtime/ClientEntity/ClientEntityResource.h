#pragma once

#include "Foundation/Delegate/DelegateList.h"

#include "Runtime/DocumentResource/DocumentResourceBase.h"
#include "Runtime/DocumentResource/DocumentResourcePtr.h"
#include "Runtime/ClientEntity/ClientEntityDef.refl.h"
#include "Runtime/Sprite/SpriteResource.h"

class ClientEntityResource;
class AnimationState;

using ClientEntityResourcePtr = DocumentResourcePtr<ClientEntityDef, ClientEntityResource>;
using EntityLoadLink = DocumentResourceLoadCallbackLink<ClientEntityDef, ClientEntityResource>;

class ClientEntityResource : public DocumentResourceBase
{
public:
  ClientEntityResource(Any && load_data, uint32_t path_hash, czstr path);

  NotNullPtr<ClientEntityDef> GetData();
  EntityLoadLink AddLoadCallback(Delegate<void, NotNullPtr<ClientEntityResource>> && callback);
  void AddLoadCallback(Delegate<void, NotNullPtr<ClientEntityResource>> && callback, EntityLoadLink & link);

  static ClientEntityResourcePtr Find(uint32_t file_path_hash);
  static ClientEntityResourcePtr Load(czstr file_path);
  static EntityLoadLink LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<ClientEntityResource>> && callback);
  static void LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<ClientEntityResource>> && callback, EntityLoadLink & link);

  SpritePtr & GetSprite();
  const SpritePtr & GetSprite() const;

protected:
  virtual void OnDataLoadComplete(const std::string & resource_data) override;
  virtual void CallAssetLoadCallbacks() override;

private:

  friend class ClientEntitySystem;

  ClientEntityDef m_Data;
  DelegateList<void, NotNullPtr<ClientEntityResource>> m_LoadCallbacks;

  SpritePtr m_Sprite;
};
