#pragma once

struct GameInstanceData;
class GameController;
class ServerObjectManager;
class ServerObjectEventSystem;
class GameServerEventSender;
class GameSimulationEventCallbacks;
class GameLogicSystems;
class GameStage;
class GameSharedGlobalResources;
class GameSharedInstanceResources;

class GameLogicContainer
{
public:
  GameLogicContainer(
    GameController & game_controller,
    GameInstanceData & global_data,
    ServerObjectManager & object_manager,
    ServerObjectEventSystem & server_object_event_system,
    GameServerEventSender & server_event_sender,
    GameSimulationEventCallbacks & sim_event_sender,
    GameSharedGlobalResources & shared_global_resources,
    GameSharedInstanceResources & shared_instance_resources,
    GameLogicSystems & systems,
    const GameStage & stage, 
    bool is_authority,
    int & send_timer);

  GameLogicContainer(const GameLogicContainer & rhs) = default;
  GameLogicContainer(GameLogicContainer && rhs) = default;

  GameLogicContainer & operator = (const GameLogicContainer & rhs) = default;
  GameLogicContainer & operator = (GameLogicContainer && rhs) = default;

  GameController & GetGameController();
  GameInstanceData & GetInstanceData();
  ServerObjectManager & GetObjectManager();
  ServerObjectEventSystem & GetServerObjectEventSystem();
  GameServerEventSender & GetEventSender();
  GameSimulationEventCallbacks & GetSimEventCallbacks();
  GameSharedGlobalResources & GetSharedGlobalResources();
  GameSharedInstanceResources & GetSharedInstanceResources();
  GameLogicSystems & GetSystems();
  const GameStage & GetStage();
  bool IsAuthority();
  void TriggerImmediateSend();

private:
  GameController & m_GameController;
  GameInstanceData & m_InstanceData;
  ServerObjectManager & m_ObjectManager;
  ServerObjectEventSystem & m_ObjectEventSystem;
  GameServerEventSender & m_ServerEventSender;
  GameSimulationEventCallbacks & m_SimEventSender;
  GameSharedGlobalResources & m_SharedGlobalResources;
  GameSharedInstanceResources & m_SharedInstanceResources;
  GameLogicSystems & m_Systems;
  const GameStage & m_Stage;
  bool m_IsAuthority;
  int & m_SendTimer;
};
