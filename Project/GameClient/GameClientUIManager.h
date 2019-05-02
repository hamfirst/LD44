#pragma once

#include "Engine/UI/UIManager.h"

#include "ProjectSettings/ProjectNetworkSettings.h"

#include "Foundation/Sequencer/Sequencer.h"
#include "Foundation/Time/FPSClock.h"

#include "GameClient/GameClientUIData.refl.h"

class GameContainer;
class GameClientEventSender;
class GameCamera;

class RenderState;

struct GameFullState;
struct GameClientUIData;
struct GameInstanceData;

class GameClientUIManager
{
public:
  GameClientUIManager(GameContainer & container, int local_index = 0);
  ~GameClientUIManager();

  void Update();
  void Render();

  void ShowQuitPopup();
  void CancelPopup();

  void ShowTutorial();
  bool IsPopupOpen();

  bool IsBlocking();
  bool WantsToQuit();

  UIManager & GetUIManager();

  void AddNoiseAlert(float angle, float alpha);

protected:

  GameClientUIData GetScriptData();

  void Quit();

  void BuyDamage();
  void BuyAmmo();
  void BuyHealth();
  void BuySpeed();
  void BuyLife();
  void BuyRate();

private:

  GameContainer & m_GameContainer;
  int m_LocalIndex;

  bool m_WantsToQuit;
  bool m_PopupOpen;
  bool m_ShopOpen;

  bool m_DrawProfileData = false;
  bool m_DrawFPS = false;
  bool m_RefreshShop = false;
  FPSClock m_FPSClock;
  StopWatch m_UpdateClock;

  std::vector<NoiseAlert> m_Alerts;
};

