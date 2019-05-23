#include "GameClient/GameClientCommon.h"
#include "GameClient/Modes/GameModeEndGame.h"
#include "GameClient/Modes/GameModeMainMenu.h"
#include "GameClient/Modes/GameModeConnectingGame.h"
#include "GameClient/Modes/GameModeSinglePlayerBots.h"
#include "GameClient/Modes/GameModeOfflineStaging.h"
#include "GameClient/GameContainer.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Entity/ClientEntitySystem.h"
#include "Engine/ClientComponent/ClientComponentSystem.h"
#include "Engine/ClientComponent/ClientComponentUpdateBucketList.h"
#include "Engine/Map/MapSystem.h"
#include "Engine/VisualEffect/VisualEffectManager.h"
#include "Engine/DrawList/DrawList.h"
#include "Engine/EngineState.h"
#include "Engine/Audio/MusicManager.h"

GameModeEndGame::GameModeEndGame(GameContainer & game, std::unique_ptr<GameClientInstanceContainer> && instance_container,
                                                       std::unique_ptr<GameClientSystems> && client_systems, EndGamePlayAgainMode mode) :
  GameMode(game),
  m_InstanceContainer(std::move(instance_container)),
  m_ClientSystems(std::move(client_systems)),
  m_Mode(mode)
{

}

GameModeEndGame::~GameModeEndGame()
{

}

void GameModeEndGame::Initialize()
{
  m_Victory = false;

  auto & game_state = m_InstanceContainer->GetGlobalInstanceData();
  auto & game_data = m_InstanceContainer->GetLowFrequencyData();

  auto num_local_players = m_InstanceContainer->GetNumLocalData();
  for (std::size_t client_index = 0; client_index < num_local_players; ++client_index)
  {
    auto & local_data = m_InstanceContainer->GetClientLocalData(client_index);
    auto & local_player = game_data.m_Players[(int)local_data.m_PlayerIndex];

    if (game_state.m_WiningTeam && game_state.m_WiningTeam.Value() == local_player.m_Team)
    {
      m_Victory = true;
    }
  }
}

void GameModeEndGame::OnAssetsLoaded()
{
  g_MusicManager.FadeOut(0.1f);
  if (m_Victory)
  {
    //g_MusicManager.PlayClip(container.GetClientGlobalResources().VictoryMusic, 0.5f, true);
  }
  else
  {
    //g_MusicManager.PlayClip(container.GetClientGlobalResources().DefeatMusic, 0.5f, true);
  }

  m_StopWatch.Start();
  m_FrameClock.Start();
}

void GameModeEndGame::Update()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  container.GetWindow().Update();
  container.UpdateUIManager();

  auto & ui_manager = container.GetClientSystems()->GetUIManager();
  auto & input_manager = container.GetClientSystems()->GetInputManager();

  auto & engine_state = container.GetEngineState();
  auto comp_system = engine_state.GetComponentSystem();
  auto entity_system = engine_state.GetEntitySystem();
  auto visual_effects = engine_state.GetVisualEffectManager();
  auto map_system = engine_state.GetMapSystem();

  if (m_FrameClock.ShouldSkipFrameUpdate() == false)
  {
    m_FrameClock.BeginFrame();
    container.GetWindow().Update();

    input_manager.Update();

    if (m_StopWatch.GetTimeSinceStart() < 2.0f)
    {
      entity_system->BeginFrame();
      m_InstanceContainer->Update();

      map_system->UpdateAllMaps(container);

      ClientComponentUpdateBucketList update_list;
      comp_system->CreateUpdateBucketList(update_list);

      for (int index = 0, end = update_list.GetNumBuckets(); index < end; ++index)
      {
        update_list.CallFirst(index);
        entity_system->FinalizeEvents();

        update_list.CallMiddle(index);
        entity_system->FinalizeEvents();

        update_list.CallLast(index);
        entity_system->FinalizeEvents();
      }
    }
  }

  auto & camera = container.GetClientSystems()->GetCamera();
  auto viewport_bounds = Box::FromFrameCenterAndSize(camera.GetOffsetPosition(), camera.GetGameResolution());

  visual_effects->Update(viewport_bounds);

  ui_manager.Update();

  if (ui_manager.WantsToQuit())
  {
    auto & container = GetContainer();
    container.SwitchMode<GameModeMainMenu>();
  }
}

void GameModeEndGame::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & ui_manager = container.GetClientSystems()->GetUIManager();
  auto & input_manager = container.GetClientSystems()->GetInputManager();
  auto & camera = container.GetClientSystems()->GetCamera();

  render_state.SetScreenSize(container.GetWindow().GetSize());
  render_state.SetRenderSize(camera.GetGameResolution());

  render_state.SetDefaultClearColor();
  render_state.Clear();

  auto & engine_state = container.GetEngineState();
  auto entity_system = engine_state.GetEntitySystem();
  auto map_system = engine_state.GetMapSystem();

  auto screen_resolution = container.GetWindow().GetSize();

  camera.SetScreenResolution(screen_resolution);
  camera.Update();

  auto viewport_bounds = Box::FromFrameCenterAndSize(camera.GetOffsetPosition(), camera.GetGameResolution());

  camera.Draw(container, &engine_state, render_state);

  input_manager.Render();
  ui_manager.Render();

  container.RenderUIManager();
}

void GameModeEndGame::PlayAgain()
{
  auto & container = GetContainer();
  auto & init_settings = container.GetInstanceData()->GetLowFrequencyData().m_Settings;

  switch (m_Mode)
  {
  case EndGamePlayAgainMode::kOnlineGameplay:

    break;
  case EndGamePlayAgainMode::kOfflineMultiplayer:
    container.SwitchMode<GameModeOfflineStaging>(init_settings);
    break;
  case EndGamePlayAgainMode::kOfflineSingleplayer:
    container.SwitchMode<GameModeSinglePlayerBots>(init_settings, false);
    break;
  }
}

void GameModeEndGame::Quit()
{
  auto & container = GetContainer();
  container.SwitchMode<GameModeMainMenu>();
}