#include <Project/Game/GameNetworkData.refl.h>
#include "GameShared/GameSharedCommon.h"
#include "GameShared/GameServerWorld.h"

GameServerWorld::GameServerWorld(
  GameController & game_controller,
  const GameInitSettings & init_settings,
  GameInstanceData & global_data,
  GameInstanceLowFrequencyData & low_freq_data,
  ServerEntityManager & object_manager,
  ServerEntityEventSystem & server_object_event_system,
  GameServerEventSender & server_event_sender,
  GameSimulationEventCallbacks & sim_event_sender,
  GameLogicSystems & systems,
  const GameStage & stage,
  bool is_authority,
  int & send_timer,
  bool & modified_low_freq_data) :
  m_GameController(game_controller),
  m_InitSettings(init_settings),
  m_InstanceData(global_data),
  m_LowFrequencyData(low_freq_data),
  m_ObjectManager(object_manager),
  m_ObjectEventSystem(server_object_event_system),
  m_ServerEventSender(server_event_sender),
  m_SimEventSender(sim_event_sender),
  m_Systems(systems),
  m_Stage(stage),
  m_IsAuthority(is_authority),
  m_SendTimer(send_timer),
  m_ModifiedLowFreqData(modified_low_freq_data),
  m_AllowModifyLowFreqData(false)
{

}

GameController & GameServerWorld::GetGameController()
{
  return m_GameController;
}

const GameInitSettings & GameServerWorld::GetGameInitSettings()
{
  return m_InitSettings;
}

GameInstanceData & GameServerWorld::GetInstanceData()
{
  return m_InstanceData;
}

const GameInstanceLowFrequencyData & GameServerWorld::GetLowFrequencyInstanceData() const
{
  return m_LowFrequencyData;
}

GameInstanceLowFrequencyData & GameServerWorld::GetLowFrequencyInstanceDataForModify()
{
  ASSERT(m_AllowModifyLowFreqData, "Modifying low freq data when not allowed");

  m_ModifiedLowFreqData = true;
  return m_LowFrequencyData;
}

ServerEntityManager & GameServerWorld::GetObjectManager()
{
  return m_ObjectManager;
}

ServerEntityEventSystem & GameServerWorld::GetServerObjectEventSystem()
{
  return m_ObjectEventSystem;
}

GameServerEventSender & GameServerWorld::GetEventSender()
{
  return m_ServerEventSender;
}

GameSimulationEventCallbacks & GameServerWorld::GetSimEventCallbacks()
{
  return m_SimEventSender;
}

GameLogicSystems & GameServerWorld::GetSystems()
{
  return m_Systems;
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

void GameServerWorld::SetAllowModifyLowFrequencyData(bool allow)
{
  m_AllowModifyLowFreqData = allow;
}
