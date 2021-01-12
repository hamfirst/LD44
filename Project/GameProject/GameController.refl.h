#pragma once

#include "Foundation/Common.h"

#include "ProjectSettings/ProjectNetworkSettings.h"

#include "GameProject/GameNetworkData.refl.h"
#include "GameProject/GameNetworkEvents.refl.h"
#include "GameProject/GameNetworkExternals.refl.h"
#include "GameProject/GameFullState.refl.h"

class GameServerWorld;

class GameController
{
public:
  STORM_REFL;
  STORM_REFL_FUNCS;
  STORM_REFL_NODEFAULT;

  GameController();

  void BootstrapGame(GameServerWorld & game, uint32_t seed);

  void ConstructPlayer(std::size_t player_index, GameServerWorld & game, const std::string & name, int team);
  void DestroyPlayer(std::size_t player_index, GameServerWorld & game);
  bool AllowConversionToBot(std::size_t player_index, GameServerWorld & game);
  void ConvertBotToPlayer(std::size_t player_index, GameServerWorld & game, const std::string & name);

  void ConstructBot(std::size_t player_index, GameServerWorld & game, const std::string & name, int team);
  void DestroyBot(std::size_t player_index, GameServerWorld & game);
  void ConvertPlayerToBot(std::size_t player_index, GameServerWorld & game, const std::string & name);

#ifdef NET_ALLOW_OBSERVERS
  void ConstructObserver(std::size_t observer_index, GameServerWorld & game, const std::string & name);
  void DestroyObserver(std::size_t observer_index, GameServerWorld & game);

#ifdef NET_USE_LOADOUT
  void ConvertObserverToPlayer(std::size_t observer_index, std::size_t player_index, GameServerWorld & game, int team,
          uint32_t random_number, const GamePlayerLoadout & loadout);
#else
  void ConvertObserverToPlayer(std::size_t observer_index, std::size_t player_index,
          GameServerWorld & game, int team, uint32_t random_number);
#endif

  void ConvertPlayerToObserver(std::size_t observer_index, std::size_t player_index, GameServerWorld & game, bool replace_with_bot = true);
#endif

  void ProcessExternal(const NetPolymorphic<GameNetworkExternalEvent> & ext, GameServerWorld & game);

  void InitPlayer(GameServerWorld & game, std::size_t player_index, const GamePlayer & player);
  void SetPlayerToSpawn(GameServerWorld & game, std::size_t player_index) const;
  void CleanupPlayer(GameServerWorld & game, std::size_t player_index);
  int AddAIPlayer(GameServerWorld & game, uint32_t random_number);
  void FillWithBots(GameServerWorld & game, uint32_t random_number);

  int GetMaxPlayerCount(GameServerWorld & game) const;

#ifdef NET_USE_SCORE
  int GetScoreLimit(GameServerWorld & game) const;
#endif

#ifdef NET_USE_ROUND_TIMER
  void RoundStarted(GameServerWorld & game) const;
  void RoundEnded(GameServerWorld & game) const;
  void RoundReset(GameServerWorld & game) const;
  int GetTimeLimit(GameServerWorld & game) const;
#endif

  static std::vector<int> GetTeamCounts(const GameInstanceLowFrequencyData & game_data);
  static std::vector<int> GetTeamCounts(const GameStateLoading & game_data);
  Optional<int> GetOnlyTeamWithPlayers(GameServerWorld & game);
  Optional<int> GetDefaultWinningTeam();

  void HandleClientEvent(std::size_t player_index, GameServerWorld & game, std::size_t event_class_id, const void * event_ptr);
  void HandleAuthEvent(GameServerWorld & game, std::size_t event_class_id, const void * event_ptr);

  bool ValidateInput(std::size_t player_index, GameServerWorld & game, ClientInput & input);
  void ApplyInput(std::size_t player_index, GameServerWorld & game, const ClientInput & input);
  void Update(GameServerWorld & game);

  void StartGame(GameServerWorld & game);
  void EndGame(int winning_team, GameServerWorld & game);

#ifdef NET_USE_SCORE
  void AddScore(int team, GameServerWorld & game, GameNetVec2 & pos);
#endif

  void STORM_REFL_FUNC HandlePlaceholderEvent(const PlaceholderClientEvent & ev, std::size_t player_index, GameServerWorld & game);
  void STORM_REFL_FUNC HandlePlaceholderAuthEvent(const PlaceholderServerAuthEvent & ev, GameServerWorld & game);

#if PROJECT_PERSPECTIVE == PERSPECTIVE_SIDESCROLLER
  void STORM_REFL_FUNC HandleJumpEvent(const JumpEvent & ev, std::size_t player_index, GameServerWorld & game);
#endif

#ifdef NET_USE_AIM_DIRECTION
  void STORM_REFL_FUNC HandleFireEvent(const FireEvent & ev, std::size_t player_index, GameServerWorld & game);
#endif

  void STORM_REFL_FUNC HandleUseEvent(const UseEvent & ev, std::size_t player_index, GameServerWorld & game);
  void STORM_REFL_FUNC HandlePurchaseEvent(const PurchaseEvent & ev, std::size_t player_index, GameServerWorld & game);

  void RespawnNPCs(GameServerWorld & game) const;

private:

  template <typename Visitor>
  void VisitPlayers(GameServerWorld & game, Visitor && visitor) const;

private:

  std::vector<Delegate<void, const void *, std::size_t, GameServerWorld &>> m_ClientEventCallbacks;
  std::vector<Delegate<void, const void *, GameServerWorld &>> m_AuthEventCallbacks;

  // There should be no state in this class since it's designed to only respond to events using the GameServerWorld
};

