#include <Project/Game/GameNetworkData.refl.h>
#include "GameShared/GameSharedCommon.h"
#include "GameServerWorld.h"

GameServerWorld::GameServerWorld(
  const GameInitSettings & init_settings,
  const GameStage & stage,
  bool is_authority,
  int & send_timer) :
  m_InitSettings(init_settings),
  m_Stage(stage),
  m_IsAuthority(is_authority),
  m_SendTimer(send_timer)
{

}

const GameInitSettings & GameServerWorld::GetGameInitSettings()
{
  return m_InitSettings;
}

const GameStage & GameServerWorld::GetStage()
{
  return m_Stage;
}

bool GameServerWorld::IsAuthority()
{
  return m_IsAuthority;
}

void GameServerWorld::TriggerImmediateSend()
{
  m_SendTimer = 0;
}
