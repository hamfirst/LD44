#pragma once

struct GameInstanceData;
struct GameInstanceLowFrequencyData;
struct GameInitSettings;
class GameController;
class ServerEntityManager;
class ServerEntityEventSystem;
class GameServerEventSender;
class GameSimulationEventCallbacks;
class GameLogicSystems;
class GameStage;

class GameServerWorld
{
public:
  GameServerWorld(
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
    bool & modified_low_freq_data);

  GameServerWorld(const GameServerWorld & rhs) = default;
  GameServerWorld(GameServerWorld && rhs) = default;

  GameController & GetGameController();
  const GameInitSettings & GetGameInitSettings();
  GameInstanceData & GetInstanceData();
  const GameInstanceLowFrequencyData & GetLowFrequencyInstanceData() const;
  GameInstanceLowFrequencyData & GetLowFrequencyInstanceDataForModify();
  ServerEntityManager & GetObjectManager();
  ServerEntityEventSystem & GetServerObjectEventSystem();
  GameServerEventSender & GetEventSender();
  GameSimulationEventCallbacks & GetSimEventCallbacks();
  GameLogicSystems & GetSystems();
  const GameStage & GetStage();
  bool IsAuthority();
  void TriggerImmediateSend();

  void SetAllowModifyLowFrequencyData(bool allow);

private:
  GameController & m_GameController;
  const GameInitSettings & m_InitSettings;
  GameInstanceData & m_InstanceData;
  GameInstanceLowFrequencyData & m_LowFrequencyData;
  ServerEntityManager & m_ObjectManager;
  ServerEntityEventSystem & m_ObjectEventSystem;
  GameServerEventSender & m_ServerEventSender;
  GameSimulationEventCallbacks & m_SimEventSender;
  GameLogicSystems & m_Systems;
  const GameStage & m_Stage;
  bool m_IsAuthority;
  int & m_SendTimer;
  bool & m_ModifiedLowFreqData;
  bool m_AllowModifyLowFreqData;
};


