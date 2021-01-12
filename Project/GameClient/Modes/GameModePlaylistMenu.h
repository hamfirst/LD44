#pragma once

#include "GameClient/Modes/GameModeOnlineBase.h"

#include "Project/GameShared/PlayList/GamePlayList.h"

#include "Engine/UI/UIManager.h"

class GameModePlaylistMenu : public GameModeOnlineBase
{
public:
  GameModePlaylistMenu(GameContainer & game, bool competitive);
  ~GameModePlaylistMenu();

  void Initialize() override;
  void Deinit() override;
  void OnAssetsLoaded() override;

  void Update() override;
  void Render() override;

protected:

  void Search(int playlist_mask);
  void Back();

private:

  GamePlayList m_CasualPlaylist;
  GamePlayList m_CompetitivePlaylist;

  bool m_Competitive;
};
