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
    const GameInitSettings & init_settings,
    const GameStage & stage, 
    bool is_authority,
    int & send_timer);

  GameServerWorld(const GameServerWorld & rhs) = default;
  GameServerWorld(GameServerWorld && rhs) = default;

  const GameInitSettings & GetGameInitSettings();
  const GameStage & GetStage();
  bool IsAuthority();
  void TriggerImmediateSend();

private:
  const GameInitSettings & m_InitSettings;
  const GameStage & m_Stage;
  bool m_IsAuthority;
  int & m_SendTimer;
};


