
#pragma once

#include "GameClient/GameClientCommon.h"
#include "Runtime/ClientComponent/ClientComponentInitData.refl.h"
#include "Engine/ClientComponent/ClientComponent.h"

struct SyncServerObjectComponentInitData : public ClientComponentInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(SyncServerObjectComponentInitData);

  RBool m_SyncSprite;
};

class SyncServerObjectComponent : public ClientComponent
{
public:
  DECLARE_CLIENT_COMPONENT;

  SyncServerObjectComponent(SyncServerObjectComponentInitData && init_data);
  virtual ~SyncServerObjectComponent();

  void UpdateFirst();

  virtual void ServerDestroy() override;

private:
  bool m_SyncSprite;
};
