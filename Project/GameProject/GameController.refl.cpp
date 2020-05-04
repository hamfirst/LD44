#include "Game/GameCommon.h"

#include "Foundation/Pathfinding/Pathfinding.h"

#include "GameShared/Systems/GameLogicSystems.h"
#include "GameShared/GameServerWorld.h"

#include "Game/GameController.refl.meta.h"
#include "Game/GameNetworkData.refl.meta.h"
#include "Game/GameNetworkEvents.refl.meta.h"
#include "Game/GameSimulationEventCallbacks.h"
#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"
#include "Game/AI/PlayerAI.h"
#include "Game/GameConfig.refl.meta.h"
#include "Game/ServerEntities/Player/PlayerServerEntity.refl.meta.h"
#include "Game/ServerEntities/Bot/NPC/NPCBot.refl.meta.h"

#include "Runtime/ServerEntity/ServerEntityManager.h"

#include "LobbyShared/LobbyGameFuncs.h"

#include "StormRefl/StormReflMetaCall.h"


GLOBAL_ASSET(ConfigPtr<GameConfig>, "./Configs/GameConfig.gameconfig", g_GameConfig);

CLIENT_ASSET(ClientAssetType::kAudio, "./Sounds/BatChirps.wav", g_BatChirpsAudio);

#define SHUFFLE_SPAWNS

struct GameControllerRegister
{
  template <typename ParamType>
  static void Register(
    GameController * ptr, 
    std::vector<Delegate<void, const void *, std::size_t, GameServerWorld &>> & client_events,
    std::vector<Delegate<void, const void *, GameServerWorld &>> & auth_events,
    void (GameController::*func_ptr)(const ParamType &, std::size_t, GameServerWorld &))
  {
    static_assert(std::is_base_of<ClientNetworkEvent, ParamType>::value, "Client event handlers must have a parameter that inherits from ClientNetworkEvent");

    auto class_id = ClientNetworkEvent::__s_TypeDatabase.GetClassId<ParamType>();
    client_events[class_id] = Delegate<void, const void *, std::size_t, GameServerWorld &>(
      [=](const void * ev, std::size_t player_index, GameServerWorld & game) { (ptr->*func_ptr)(*(const ParamType *)ev, player_index, game); });
  }

  template <typename ParamType>
  static void Register(
    GameController * ptr,
    std::vector<Delegate<void, const void *, std::size_t, GameServerWorld &>> & client_events,
    std::vector<Delegate<void, const void *, GameServerWorld &>> & auth_events,
    void (GameController::*func_ptr)(const ParamType &, GameServerWorld &))
  {
    static_assert(std::is_base_of<ServerAuthNetworkEvent, ParamType>::value, "Auth event handlers must have a parameter that inherits from ServerAuthNetworkEvent");

    auto class_id = ServerAuthNetworkEvent::__s_TypeDatabase.GetClassId<ParamType>();
    auth_events[class_id] = Delegate<void, const void *, GameServerWorld &>(
      [=](const void * ev, GameServerWorld & game) { (ptr->*func_ptr)(*(const ParamType *)ev, game); });
  }
};

GameController::GameController()
{
  auto num_client_types = ClientNetworkEvent::__s_TypeDatabase.GetNumTypes();
  m_ClientEventCallbacks.resize(num_client_types);

  auto num_auth_types = ServerAuthNetworkEvent::__s_TypeDatabase.GetNumTypes();
  m_AuthEventCallbacks.resize(num_auth_types);

  auto visitor = [&](auto f)
  {
    using FuncType = decltype(f);
    using ParamType = typename std::decay_t<typename FuncType::template param_info<0>::param_type>;

    auto func_ptr = FuncType::GetFunctionPtr();
    GameControllerRegister::Register(this, m_ClientEventCallbacks, m_AuthEventCallbacks, func_ptr);
  };

  StormReflVisitFuncs(*this, visitor);
}

void GameController::BootstrapGame(GameServerWorld & game, uint32_t seed)
{
#ifdef NET_USE_RANDOM
  auto & sim_data = game.GetInstanceData();
  sim_data.m_Random = NetRandom(seed);
  sim_data.m_Random.GetRandom();
  sim_data.m_Random.GetRandom();
  sim_data.m_Random.GetRandom();
  sim_data.m_Random.GetRandom();
#endif
}

void GameController::ConstructPlayer(std::size_t player_index, GameServerWorld & game, const std::string & name, int team)
{
  GamePlayer player;
  player.m_UserName = name;
  player.m_Team = team;

  auto & data = game.GetLowFrequencyInstanceDataForModify();
  data.m_Players.EmplaceAt(player_index, std::move(player));
}

void GameController::DestroyPlayer(std::size_t player_index, GameServerWorld & game)
{
  CleanupPlayer(game, player_index);
}

bool GameController::AllowConversionToBot(std::size_t player_index, GameServerWorld & game)
{
  auto & global_data = game.GetLowFrequencyInstanceData();
  auto player = global_data.m_Players.TryGet(player_index);

  if (player == nullptr)
  {
    return true;
  }

  auto game_data = game.GetInstanceData();
#ifdef NET_USE_SCORE
  auto max_score = GetScoreLimit(game);
  if (game_data.m_Score[(int)player->m_Team] > max_score / 2)
  {
    return false;
  }
#endif

  if(game_data.m_AIPlayerInfo.HasAt(player_index))
  {
    return false;
  }

  return true;
}

void GameController::ConvertBotToPlayer(std::size_t player_index, GameServerWorld & game, const std::string & name)
{
  auto & global_data = game.GetLowFrequencyInstanceDataForModify();
  auto player = global_data.m_Players.TryGet(player_index);

  player->m_UserName = name;

  auto & game_data = game.GetInstanceData();
  game_data.m_AIPlayerInfo.RemoveAt(player_index);
}

void GameController::ConstructBot(std::size_t player_index, GameServerWorld & game, const std::string & name, int team)
{
  GamePlayer player;
  player.m_UserName = name;
  player.m_Team = team;

  auto & global_data = game.GetLowFrequencyInstanceDataForModify();
  global_data.m_Players.EmplaceAt(player_index, std::move(player));

  auto & game_state = game.GetInstanceData();
  game_state.m_AIPlayerInfo.EmplaceAt(player_index);
}

void GameController::DestroyBot(std::size_t player_index, GameServerWorld & game)
{
  auto & global_data = game.GetLowFrequencyInstanceDataForModify();
  global_data.m_Players.RemoveAt(player_index);

  auto & game_state = game.GetInstanceData();
  game_state.m_AIPlayerInfo.RemoveAt(player_index);
}

void GameController::ConvertPlayerToBot(std::size_t player_index, GameServerWorld & game, const std::string & name)
{
  auto & global_data = game.GetLowFrequencyInstanceDataForModify();
  auto player = global_data.m_Players.TryGet(player_index);

  player->m_UserName = name;

  auto & game_state = game.GetInstanceData();
  game_state.m_AIPlayerInfo.EmplaceAt(player_index, AIPlayerInfo{});
}

#ifdef NET_ALLOW_OBSERVERS
void GameController::ConstructObserver(std::size_t observer_index, GameServerWorld & game, const std::string & name)
{
  GameObserver player;
  player.m_UserName = name;

  auto & global_data = game.GetLowFrequencyInstanceDataForModify();
  global_data.m_Observers.EmplaceAt(observer_index, std::move(player));
}

void GameController::DestroyObserver(std::size_t observer_index, GameServerWorld & game)
{
  auto & global_data = game.GetLowFrequencyInstanceDataForModify();
  global_data.m_Observers.RemoveAt(observer_index);
}


#ifdef NET_USE_LOADOUT
void GameController::ConvertObserverToPlayer(std::size_t observer_index, std::size_t player_index,
        GameServerWorld & game, int team, uint32_t random_number, const GamePlayerLoadout & loadout)
#else
void GameController::ConvertObserverToPlayer(std::size_t observer_index, std::size_t player_index,
        GameServerWorld & game, int team, uint32_t random_number)
#endif
{
  auto & game_data = game.GetLowFrequencyInstanceDataForModify();
  auto & user_name = game_data.m_Observers[observer_index].m_UserName;
  game_data.m_Observers.RemoveAt(observer_index);

  auto & stage = game.GetStage();
  auto & map_props = stage.GetMapProperties();

  GamePlayer player;
  player.m_UserName = user_name;

#ifdef NET_USE_LOADOUT
  player.m_Loadout = loadout;
#endif

  if(team < 0)
  {
    auto team_counts = GetTeamCounts(game_data);
    player.m_Team = GetRandomTeam(team_counts, random_number, map_props, game.GetGameInitSettings());
  }
  else
  {
    player.m_Team = team;
  }

  game_data.m_Players.EmplaceAt(player_index, std::move(player));
}

void GameController::ConvertPlayerToObserver(std::size_t observer_index, std::size_t player_index, GameServerWorld & game, bool replace_with_bot)
{
  auto & game_data = game.GetLowFrequencyInstanceDataForModify();
  auto & user_name = game_data.m_Players[player_index].m_UserName;
  auto & team = game_data.m_Players[player_index].m_Team;
  game_data.m_Players.RemoveAt(player_index);

  GameObserver observer;
  observer.m_UserName = user_name;

  game_data.m_Observers.EmplaceAt(observer_index, std::move(observer));

#ifdef NET_FILL_WITH_BOTS
  if(replace_with_bot)
  {
    ConstructBot(player_index, game, "AI", team);
  }
  else
#endif
  {
    CleanupPlayer(game, player_index);
  }
}

#endif

void GameController::ProcessExternal(const NetPolymorphic<GameNetworkExternalEvent> & ext, GameServerWorld & game)
{
  auto & stage = game.GetStage();
  auto & map_props = stage.GetMapProperties();
  auto & game_settings = game.GetGameInitSettings();

  if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<PlayerJoinedEvent>())
  {
    auto ev = ext.Get<PlayerJoinedEvent>();
    ConstructPlayer(ev->m_PlayerIndex, game, ev->m_UserName, ev->m_Team);
  }
  else if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<PlayerLeaveEvent>())
  {
    auto ev = ext.Get<PlayerLeaveEvent>();
    DestroyPlayer(ev->m_PlayerIndex, game);
  }
  else if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<ChangePlayerNameEvent>())
  {
    auto ev = ext.Get<ChangePlayerNameEvent>();
    auto & game_state = game.GetLowFrequencyInstanceDataForModify();
    game_state.m_Players[ev->m_PlayerIndex].m_UserName = ev->m_Name;
  }
  else if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<ChangePlayerTeam>())
  {
    auto ev = ext.Get<ChangePlayerTeam>();
    auto & game_state = game.GetLowFrequencyInstanceDataForModify();
    game_state.m_Players[ev->m_PlayerIndex].m_Team = ev->m_Team;
  }
#ifdef NET_USE_LOADOUT
  else if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<ChangeLoadoutEvent>())
  {
    auto ev = ext.Get<ChangeLoadoutEvent>();
    auto & game_state = game.GetLowFrequencyInstanceDataForModify();
    game_state.m_Players[ev->m_PlayerIndex].m_Loadout = ev->m_Loadout;
  }
#endif
#ifdef NET_ALLOW_OBSERVERS
  else if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<ObserverJoinedEvent>())
  {
    auto ev = ext.Get<ObserverJoinedEvent>();
    ConstructObserver(ev->m_PlayerIndex, game, ev->m_UserName);
  }
  else if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<ObserverLeaveEvent>())
  {
    auto ev = ext.Get<ObserverLeaveEvent>();
    DestroyObserver(ev->m_PlayerIndex, game);
  }
  else if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<ChangeObserverNameEvent>())
  {
    auto ev = ext.Get<ChangeObserverNameEvent>();
    auto & game_state = game.GetLowFrequencyInstanceDataForModify();
    game_state.m_Observers[ev->m_ObserverIndex].m_UserName = ev->m_Name;
  }
  else if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<ChangeObserverToPlayer>())
  {
    auto ev = ext.Get<ChangeObserverToPlayer>();

#ifdef NET_USE_LOADOUT
    ConvertObserverToPlayer(ev->m_ObserverIndex, ev->m_PlayerIndex, game, ev->m_Team, ev->m_RandomSeed, ev->m_Loadout);
#else
    ConvertObserverToPlayer(ev->m_ObserverIndex, ev->m_PlayerIndex, game, ev->m_Team, ev->m_RandomSeed);
#endif
  }
  else if (ext.GetClassId() == GameNetworkExternalEvent::__s_TypeDatabase.GetClassId<ChangePlayerToObserver>())
  {
    auto ev = ext.Get<ChangePlayerToObserver>();
    ConvertPlayerToObserver(ev->m_ObserverIndex, ev->m_PlayerIndex, game);
  }
#endif

}

void GameController::InitPlayer(GameServerWorld & game, std::size_t player_index, const GamePlayer & player)
{
  auto & obj_manager = game.GetObjectManager();

  auto player_obj = obj_manager.CreateDynamicEntity<PlayerServerEntity>(player_index, game);
  StormReflSefDefault(*player_obj);

  SetPlayerToSpawn(game, player_index);

  auto & game_state = game.GetInstanceData();
  if (game_state.m_AIPlayerInfo.HasAt(player_index))
  {
    PlayerAI::InitAI(game, player_index);
  }
}

void GameController::SetPlayerToSpawn(GameServerWorld & game, std::size_t player_index) const
{
  auto & stage = game.GetStage();
  auto & spawns = stage.GetPlayerSpawns();

  auto & player = game.GetLowFrequencyInstanceData().m_Players[player_index];
  auto player_obj = game.GetObjectManager().GetReservedSlotEntityAs<PlayerServerEntity>(player_index);

  auto player_team = (int)player.m_Team;


#ifdef SHUFFLE_SPAWNS
  std::vector<int> teams;
  for(int index = 0; index < kMaxTeams; ++index)
  {
    teams.push_back(index);
  }

  NetRandom r(game.GetInstanceData().m_Round);
  std::vector<int> shuffle_teams;

  for(int index = 0; index < kMaxTeams; ++index)
  {
    auto team = r.GetRandom() % teams.size();
    shuffle_teams.push_back(teams[team]);
    teams.erase(teams.begin() + team);
  }

  player_team = shuffle_teams[player_team];
#endif

  if (spawns[player_team].size() == 0)
  {
    player_obj->m_Position = {};
  }
  else
  {
    auto & spawn = spawns[player_team][0];
    player_obj->m_Position = GameNetVec2(spawn.x, spawn.y);
  }
}

void GameController::CleanupPlayer(GameServerWorld & game, std::size_t player_index)
{
  auto & global_data = game.GetLowFrequencyInstanceDataForModify();
  global_data.m_Players.RemoveAt(player_index);

  if (global_data.m_Players.HighestIndex() == -1)
  {
    EndGame(-1, game);
    return;
  }

//  auto & game_data = game.GetInstanceData();
//  if (kMaxTeams > 1 && game_data.m_WiningTeam)
//  {
//    auto winning_team = GetOnlyTeamWithPlayers(game);
//    if (winning_team)
//    {
//      EndGame(-1, game);
//      return;
//    }
//  }

  auto & obj_manager = game.GetObjectManager();
  auto player_obj = obj_manager.GetReservedSlotEntity(player_index);

  if (player_obj)
  {
    player_obj->Destroy(obj_manager);
  }
}

int GameController::AddAIPlayer(GameServerWorld & game, uint32_t random_number)
{
  auto & game_data = game.GetLowFrequencyInstanceData();
  for (int index = 0; index < kMaxPlayers; index++)
  {
    if (game_data.m_Players.HasAt(index) == false)
    {
      auto team_counts = GetTeamCounts(game.GetLowFrequencyInstanceData());

      auto & stage = game.GetStage();
      auto & map_props = stage.GetMapProperties();
      auto & game_settings = game.GetGameInitSettings();

      ConstructPlayer(index, game, "AI", GetRandomTeam(team_counts, random_number, map_props, game_settings));

      auto & instance_data = game.GetInstanceData();
      instance_data.m_AIPlayerInfo.EmplaceAt(index);
      return index;
    }
  }

  return -1;
}

void GameController::FillWithBots(GameServerWorld & game, uint32_t random_number)
{
  while (true)
  {
    auto team_counts = GetTeamCounts(game.GetLowFrequencyInstanceData());
    if (DoAllTeamsHavePlayers(team_counts, game.GetStage().GetMapProperties(), game.GetGameInitSettings()))
    {
      break;
    }

    int slot = -1;
    for (int index = 0; index < kMaxPlayers; ++index)
    {
      if (game.GetLowFrequencyInstanceData().m_Players.HasAt(index) == false)
      {
        slot = index;
        break;
      }
    }

    auto & stage = game.GetStage();
    auto & map_props = stage.GetMapProperties();
    auto & game_settings = game.GetGameInitSettings();

    auto team = GetRandomTeam(team_counts, random_number, map_props, game_settings);
    ConstructBot(slot, game, "AI", team);
  }
}

int GameController::GetMaxPlayerCount(GameServerWorld & game) const
{
#ifdef NET_USE_PLAYER_LIMIT
  return game.GetLowFrequencyInstanceData().m_Settings.m_PlayerCount;
#else
  return kMaxPlayers;
#endif
}

#ifdef NET_USE_SCORE
int GameController::GetScoreLimit(GameServerWorld & game) const
{
#ifdef NET_USE_SCORE_LIMIT
  return game.GetLowFrequencyInstanceData().m_Settings.m_ScoreLimit;
#else
  return kMaxScore;
#endif
}
#endif

#ifdef NET_USE_ROUND_TIMER
void GameController::RoundStarted(GameServerWorld & game) const
{
  // Vampire
  VisitPlayers(game, [&](std::size_t player_index, NotNullPtr<PlayerServerEntity> player)
  {
    player->PoofToBat(game, false);
  });

  game.GetEventSender().SendSoundEvent({}, g_BatChirpsAudio, false);
}

void GameController::RoundEnded(GameServerWorld & game) const
{

}

void GameController::RoundReset(GameServerWorld & game) const
{
  VisitPlayers(game, [&](std::size_t player_index, NotNullPtr<PlayerServerEntity> player)
  {
    SetPlayerToSpawn(game, player_index);

    // Vampire
    game.GetEventSender().SendVfxSpriteAttachedEvent(player->GetSlotIndex(),
            GameNetVec2(0, -1), COMPILE_TIME_CRC32_STR("./Sprites/Spells.sprite"), COMPILE_TIME_CRC32_STR("Spell5"));
  });

  RespawnNPCs(game);
}

int GameController::GetTimeLimit(GameServerWorld & game) const
{
#ifdef NET_USE_TIME_LIMIT
  if(game.GetLowFrequencyInstanceData().m_Settings.m_TimeLimit != 0)
  {
    game.GetLowFrequencyInstanceData().m_Settings.m_TimeLimit * 60 * 60;
  }
#endif

  return kMaxRoundTimer;
}
#endif

std::vector<int> GameController::GetTeamCounts(const GameInstanceLowFrequencyData & game_data)
{
  std::vector<int> teams(kMaxTeams);
  for (auto hero : game_data.m_Players)
  {
    teams[(int)hero.second.m_Team]++;
  }

  return teams;
}

std::vector<int> GameController::GetTeamCounts(const GameStateLoading & game_data)
{
  std::vector<int> teams(kMaxTeams);
  for (auto hero : game_data.m_Players)
  {
    if (hero.second.m_Team >= 0)
    {
      teams[(int)hero.second.m_Team]++;
    }
  }

  return teams;
}

Optional<int> GameController::GetOnlyTeamWithPlayers(GameServerWorld & game)
{
  Optional<int> team_with_players;
  for (auto player : game.GetLowFrequencyInstanceData().m_Players)
  {
    if (team_with_players)
    {
      if (team_with_players.Value() != (int)player.second.m_Team)
      {
        return{};
      }
    }
    else
    {
      team_with_players = (int)player.second.m_Team;
    }
  }

  return team_with_players;
}

Optional<int> GameController::GetDefaultWinningTeam()
{
  return{};
}

void GameController::HandleClientEvent(std::size_t player_index, GameServerWorld & game, std::size_t event_class_id, const void * event_ptr)
{
  m_ClientEventCallbacks[event_class_id].Call(event_ptr, player_index, game);
}

void GameController::HandleAuthEvent(GameServerWorld & game, std::size_t event_class_id, const void * event_ptr)
{
  m_AuthEventCallbacks[event_class_id].Call(event_ptr, game);
}

bool GameController::ValidateInput(std::size_t player_index, GameServerWorld & game, ClientInput & input)
{
#ifndef PLATFORMER_MOVEMENT
  input.m_InputStr.Clamp(0, 1);
#else
  input.m_XInput.Clamp(-1, 1);
  input.m_YInput.Clamp(-1, 1);
#endif
  return true;
}

void GameController::ApplyInput(std::size_t player_index, GameServerWorld & game, const ClientInput & input)
{
  auto server_obj = game.GetObjectManager().GetReservedSlotEntityAs<PlayerServerEntity>(player_index);
  auto player_obj = game.GetLowFrequencyInstanceData().m_Players.TryGet(player_index);

  if (player_obj && game.GetInstanceData().m_AIPlayerInfo.HasAt(player_index))
  {
    return;
  }

  if (server_obj)
  {
    server_obj->m_Input = input;
  }
}

void GameController::Update(GameServerWorld & game)
{
  auto & game_data = game.GetInstanceData();
  if (game_data.m_WiningTeam)
  {
    return;
  }

  auto & obj_manager = game.GetObjectManager();

  ServerEntityUpdateList update_list;
  obj_manager.IncrementTimeAlive();
  obj_manager.CreateUpdateList(update_list);
  obj_manager.StartUpdateLoop();

#ifdef NET_MODE_TURN_BASED_RUN
  CheckEndTurnTimer(game);

  if (game_data.m_Running == false)
  {
    return;
  }

  auto time_left = game_data.m_TimeExpiration;
  if (time_left == 0)
  {
    game_data.m_Running = false;
    game_data.m_TimeExpiration = kTurnMaxTime;
    return;
  }

  game_data.m_TimeExpiration = time_left - 1;

#endif

  auto & event_system = game.GetServerObjectEventSystem();
  auto & collision = game.GetSystems().GetCollisionDatabase();
  auto & cvc = game.GetSystems().GetCVCPushSystem();
  auto & targeting = game.GetSystems().GetTargetDatabase();

  collision.ResetDynamicCollision();
  cvc.Clear();
  targeting.Clear();

  update_list.CallFirst(game);
  event_system.FinalizeEvents(game.GetObjectManager());

  update_list.CallMiddle(game);
  event_system.FinalizeEvents(game.GetObjectManager());

  update_list.CallLast(game);
  event_system.FinalizeEvents(game.GetObjectManager());

  obj_manager.CompleteUpdateLoop();

  cvc.ProcessCVC(game);

  for (auto player : game.GetInstanceData().m_AIPlayerInfo)
  {
    PlayerAI::UpdateAI(game, player.first);
  }

#ifdef NET_USE_ROUND_TIMER

  if (game_data.m_RoundTimer > 0)
  {
    --game_data.m_RoundTimer;
  }
  else
  {
    if(game_data.m_RoundState == RoundState::kPreRound)
    {
      game_data.m_RoundState = RoundState::kRound;
      game_data.m_RoundTimer = GetTimeLimit(game);

      RoundStarted(game);
    }
    else if(game_data.m_RoundState == RoundState::kRound)
    {
      game_data.m_RoundState = RoundState::kPostRound;
      game_data.m_RoundTimer = kPostRoundTimer;

      RoundEnded(game);
    }
    else if(game_data.m_RoundState == RoundState::kPostRound)
    {
      game_data.m_RoundState = RoundState::kPreRound;
      game_data.m_RoundTimer = kPreRoundTimer;

      RoundReset(game);
    }
  }


#endif

#if NET_MODE == NET_MODE_GGPO
  game.GetInstanceData().m_FrameCount++;
#endif


  // Vampire
  if(game.GetInstanceData().m_FrameCount == 10)
  {
    VisitPlayers(game, [&](std::size_t player_index, NotNullPtr<PlayerServerEntity> player)
    {
      game.GetEventSender().SendVfxSpriteAttachedEvent(player->GetSlotIndex(),
              GameNetVec2(0, -1), COMPILE_TIME_CRC32_STR("./Sprites/Spells.sprite"), COMPILE_TIME_CRC32_STR("Spell5"));
    });
  }
}

void GameController::StartGame(GameServerWorld & game)
{
  auto & global_data = game.GetInstanceData();

#ifdef NET_USE_ROUND_TIMER
  global_data.m_RoundState = RoundState::kPreRound;
  global_data.m_RoundTimer = kPreRoundTimer;
#endif

  for (auto player : game.GetLowFrequencyInstanceData().m_Players)
  {
    InitPlayer(game, player.first, player.second);
  }

  auto & stage = game.GetStage();
  auto slot = kMaxPlayers;

  RespawnNPCs(game);

  game.TriggerImmediateSend();
}

void GameController::EndGame(int winning_team, GameServerWorld & game)
{
  game.GetInstanceData().m_WiningTeam.Emplace(winning_team);

  auto & sim_events = game.GetSimEventCallbacks();
  sim_events.HandleWinGame(winning_team);
}

#ifdef NET_USE_SCORE
void GameController::AddScore(int team, GameServerWorld & game, GameNetVec2 & pos)
{
  if (game.IsAuthority())
  {
    auto & game_data = game.GetInstanceData();
    ++game_data.m_Score[team];

    auto max_score = GetScoreLimit(game);

    auto winning_team = -1;
    for (auto team = 0; team < kMaxTeams; ++team)
    {
      if (game_data.m_Score[team] > max_score)
      {
        if (winning_team == -1)
        {
          winning_team = team;
        }
        else
        {
          winning_team = -1;
          break;
        }
      }
    }

    if (winning_team != -1)
    {
      EndGame(winning_team, game);
    }
  }
}
#endif

void GameController::HandlePlaceholderEvent(const PlaceholderClientEvent & ev, std::size_t player_index, GameServerWorld & game)
{
  auto & global_data = game.GetInstanceData();
}

void GameController::HandlePlaceholderAuthEvent(const PlaceholderServerAuthEvent & ev, GameServerWorld & game)
{

}


#if PROJECT_PERSPECTIVE == PERSPECTIVE_SIDESCROLLER
void GameController::HandleJumpEvent(const JumpEvent & ev, std::size_t player_index, GameServerWorld & game)
{
  auto server_obj = game.GetObjectManager().GetReservedSlotObjectAs<PlayerServerEntity>(player_index);
  if (server_obj)
  {
    server_obj->Jump(game);
  }
}
#endif


#ifdef NET_USE_AIM_DIRECTION
void GameController::HandleFireEvent(const FireEvent & ev, std::size_t player_index, GameServerWorld & game)
{
  auto server_obj = game.GetObjectManager().GetReservedSlotEntityAs<PlayerServerEntity>(player_index);
  if (server_obj)
  {
    server_obj->Fire(game);
  }
}
#endif

void GameController::HandleUseEvent(const UseEvent & ev, std::size_t player_index, GameServerWorld & game)
{
  auto server_obj = game.GetObjectManager().GetReservedSlotEntityAs<PlayerServerEntity>(player_index);
  if (server_obj)
  {
    server_obj->Use(game);
  }
}

void GameController::HandlePurchaseEvent(const PurchaseEvent & ev, std::size_t player_index, GameServerWorld & game)
{
  if(game.GetInstanceData().m_RoundState != RoundState::kPostRound)
  {
    return;
  }

  auto server_obj = game.GetObjectManager().GetReservedSlotEntityAs<PlayerServerEntity>(player_index);
  if (server_obj)
  {
    server_obj->PurchaseUpgrade((PlayerUpgrade)ev.m_Upgrade);
  }
}


void GameController::RespawnNPCs(GameServerWorld & game) const
{
  game.GetObjectManager().VisitEntities([&](auto index, NotNullPtr<ServerEntity> obj)
  {
    if(obj->CastTo<NPCBot>())
    {
      obj->Destroy(game.GetObjectManager());
    }
  });

  auto & stage = game.GetStage();
  auto npc_spawns = stage.GetNPCSpawns();

  for(int index = 0; index < 20 && npc_spawns.size() > 0; ++index)
  {
    auto spawn = game.GetInstanceData().m_Random.GetRandom() % npc_spawns.size();

    NPCBotInitData init_data;
    init_data.m_NPCIndex = game.GetInstanceData().m_Random.GetRandom() % 4;

    auto bot = game.GetObjectManager().CreateDynamicEntity<NPCBot>(game, &init_data);
    bot->m_Position = GameNetVec2(npc_spawns[spawn].x, npc_spawns[spawn].y);

    npc_spawns.erase(npc_spawns.begin() + spawn);
  }
}

template <typename Visitor>
void GameController::VisitPlayers(GameServerWorld & game, Visitor && visitor) const
{
  auto & obj_manager = game.GetObjectManager();
  obj_manager.VisitEntities([&](std::size_t index, NotNullPtr<ServerEntity> server_object)
  {
    auto player = server_object->CastTo<PlayerServerEntity>();
    if(player)
    {
      visitor(index, player);
    }
  });
}

