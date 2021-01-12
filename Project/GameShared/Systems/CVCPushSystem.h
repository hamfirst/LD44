#pragma once

#include "GameShared/GameSharedCommon.h"
#include "Project/GameServerFramework/GameServerWorld.h"
#include "Runtime/ServerEntity/ServerEntity.h"

class GameServerEntityBase;

class CVCPushSystem
{
public:

  void SetCharacterCVCPosition(const Box & box, NotNullPtr<GameServerEntityBase> obj);
  void ProcessCVC(GameServerWorld & game_world);

  void Clear();

private:

  struct CVCData
  {
    ServerEntityHandle m_Handle;
    Box m_Box;
  };

  std::vector<CVCData> m_Data;
};
