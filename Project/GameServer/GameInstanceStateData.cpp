
#include "GameServer/GameInstanceStateData.h"
#include "GameServer/GameInstance.h"
#include "GameServer/GameServer.h"

#include "Project/GameShared/Level/GameStageManager.h"

GameInstanceStateData::GameInstanceStateData(NotNullPtr<GameInstance> instance, const GameInitSettings & init_settings,
                                             const GameInfoTeamSizes & team_info, GameStageManager & stage_manager) :
  m_Instance(instance),
  m_StageManager(stage_manager),
  m_InitSettings(init_settings),
  m_TeamSizes(team_info)
{

}

GameInstanceStatePlayer & GameInstanceStateData::GetClient(std::size_t index)
{
  auto ptr = m_Players.TryGet(index);
  ASSERT(ptr, "Fetching invalid client");
  return *ptr;
}

const GameInitSettings & GameInstanceStateData::GetInitSettings() const
{
  return m_InitSettings;
}

const GameInfoTeamSizes & GameInstanceStateData::GetTeamInfo() const
{
  return m_TeamSizes;
}

void GameInstanceStateData::ChangeInitSettings(const GameInitSettings & init_settings)
{
  m_InitSettings = init_settings;
}

void GameInstanceStateData::NotifyLobbyNoLongerAcceptingPlayers()
{
  m_Instance->m_Server.GetGameInstanceManager().NotifyLobbyNoLongerAcceptingPlayers(m_Instance->m_GameId);
}

const GameStage & GameInstanceStateData::GetStage() const
{
  return *m_StageManager.GetStage(m_InitSettings);
}

void GameInstanceStateData::SetNewState(std::unique_ptr<GameInstanceStateBase> && state)
{
  m_Instance->SetNewState(std::move(state));
}
