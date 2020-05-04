#include "GameClient/GameClientCommon.h"
#include "GameClientUIManager.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameClientEventSender.h"
#include "GameClient/GameCamera.h"
#include "GameClient/GameClientSystems.h"
#include "GameClientUIData.refl.meta.h"

#include "Game/GameNetworkEvents.refl.h"
#include "Game/ServerEntities/Player/PlayerServerEntity.refl.h"
#include "Game/GameConfig.refl.h"

#include "Engine/Window/Window.h"
#include "Engine/Input/ControlId.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Profiler/Profiler.h"

#include "Runtime/UI/UIResource.h"

#include "Foundation/Script/ScriptDataObject.h"

extern ConfigPtr<GameConfig> g_GameConfig;

GLOBAL_ASSET(UIResourcePtr, "./UIs/QuitPopup.ui", g_QuitPopup);
GLOBAL_ASSET(UIResourcePtr, "./UIs/StoreMenu.ui", g_StoreMenu);

GameClientUIManager::GameClientUIManager(GameContainer & container, int local_index) :
  m_GameContainer(container),
  m_LocalIndex(local_index),
  m_WantsToQuit(false),
  m_PopupOpen(false),
  m_ShopOpen(false)
{

}

GameClientUIManager::~GameClientUIManager()
{

}

void GameClientUIManager::Update()
{
  auto dt = (float)m_UpdateClock.GetTimeSinceLastCheck();

  auto input_state = m_GameContainer.GetWindow().GetInputState();
  if (input_state->GetKeyPressedThisFrame(SDL_SCANCODE_ESCAPE))
  {
    if(m_PopupOpen)
    {
      CancelPopup();
    }
    else
    {
      ShowQuitPopup();
    }
  }

  if (input_state->GetKeyPressedThisFrame(SDL_SCANCODE_F11))
  {
    m_DrawFPS = !m_DrawFPS;
  }

  if (input_state->GetKeyPressedThisFrame(SDL_SCANCODE_F12))
  {
    m_DrawProfileData = !m_DrawProfileData;
  }

  if (m_RefreshShop)
  {
    CancelPopup();
    m_RefreshShop = false;
  }

  for(auto & elem : m_Alerts)
  {
    elem.alpha -= dt;
  }
  m_Alerts.erase(std::remove_if(m_Alerts.begin(), m_Alerts.end(), [](auto & elem) { return elem.alpha <= 0; }), m_Alerts.end());

  m_GameContainer.UpdateUIManager();

  GameClientUIData ui_data;

  auto ui_script_data = CreateScriptDataObject(m_GameContainer.GetUIManager()->GetScriptState(), GetScriptData());
  m_GameContainer.GetUIManager()->SetGlobal("hud_info", std::move(ui_script_data));

  auto & game_state = m_GameContainer.GetInstanceData()->GetFullState();
  auto & global_data = game_state.m_InstanceData;
  auto & client_local = m_GameContainer.GetInstanceData()->GetClientLocalData(m_LocalIndex);

  if(client_local.m_PlayerIndex != -1)
  {
    auto player_obj = game_state.m_ServerEntityManager.GetReservedSlotEntityAs<PlayerServerEntity>(client_local.m_PlayerIndex);
    if(player_obj)
    {
      UpgradeInfo upgrade_info;
      if((player_obj->m_Upgrades & (int)PlayerUpgrade::kDamage1) == 0)
      {
        upgrade_info.damage = player_obj->GetUpgradeCost(PlayerUpgrade::kDamage1);
      }
      else if((player_obj->m_Upgrades & (int)PlayerUpgrade::kDamage2) == 0)
      {
        upgrade_info.damage = player_obj->GetUpgradeCost(PlayerUpgrade::kDamage2);
      }


      if((player_obj->m_Upgrades & (int)PlayerUpgrade::kAmmo1) == 0)
      {
        upgrade_info.ammo = player_obj->GetUpgradeCost(PlayerUpgrade::kAmmo1);
      }
      else if((player_obj->m_Upgrades & (int)PlayerUpgrade::kAmmo2) == 0)
      {
        upgrade_info.ammo = player_obj->GetUpgradeCost(PlayerUpgrade::kAmmo2);
      }


      if((player_obj->m_Upgrades & (int)PlayerUpgrade::kHealth1) == 0)
      {
        upgrade_info.health = player_obj->GetUpgradeCost(PlayerUpgrade::kHealth1);
      }
      else if((player_obj->m_Upgrades & (int)PlayerUpgrade::kHealth2) == 0)
      {
        upgrade_info.health = player_obj->GetUpgradeCost(PlayerUpgrade::kHealth2);
      }

      if((player_obj->m_Upgrades & (int)PlayerUpgrade::kSpeed1) == 0)
      {
        upgrade_info.speed = player_obj->GetUpgradeCost(PlayerUpgrade::kSpeed1);
      }

      if((player_obj->m_Upgrades & (int)PlayerUpgrade::kLife1) == 0)
      {
        upgrade_info.life = player_obj->GetUpgradeCost(PlayerUpgrade::kLife1);
      }
      else if((player_obj->m_Upgrades & (int)PlayerUpgrade::kLife2) == 0)
      {
        upgrade_info.life = player_obj->GetUpgradeCost(PlayerUpgrade::kLife2);
      }
      else if((player_obj->m_Upgrades & (int)PlayerUpgrade::kLife3) == 0)
      {
        upgrade_info.life = player_obj->GetUpgradeCost(PlayerUpgrade::kLife3);
      }

      if((player_obj->m_Upgrades & (int)PlayerUpgrade::kRate1) == 0)
      {
        upgrade_info.rate = player_obj->GetUpgradeCost(PlayerUpgrade::kRate1);
      }
      else if((player_obj->m_Upgrades & (int)PlayerUpgrade::kRate2) == 0)
      {
        upgrade_info.rate = player_obj->GetUpgradeCost(PlayerUpgrade::kRate2);
      }

      m_GameContainer.GetUIManager()->SetGlobal("upgrade_info",
              CreateScriptDataObject(m_GameContainer.GetUIManager()->GetScriptState(), upgrade_info));
    }
  }

  if(game_state.m_InstanceData.m_RoundState == RoundState::kPostRound && m_ShopOpen == false && m_PopupOpen == false)
  {
    auto & ui = GetUIManager();
    auto & game_interface = ui.CreateGameInterface();

    BIND_SCRIPT_INTERFACE(game_interface, this, BuyDamage);
    BIND_SCRIPT_INTERFACE(game_interface, this, BuyAmmo);
    BIND_SCRIPT_INTERFACE(game_interface, this, BuyHealth);
    BIND_SCRIPT_INTERFACE(game_interface, this, BuySpeed);
    BIND_SCRIPT_INTERFACE(game_interface, this, BuyLife);
    BIND_SCRIPT_INTERFACE(game_interface, this, BuyRate);

    ui.PushUIDef(g_StoreMenu);

    m_ShopOpen = true;
  }
  else if(game_state.m_InstanceData.m_RoundState != RoundState::kPostRound && m_ShopOpen)
  {
    CancelPopup();
  }
}

void GameClientUIManager::Render()
{
  auto & render_state = m_GameContainer.GetRenderState();

  m_GameContainer.GetUIManager()->RenderSpecial("DrawHud", render_state);
  m_GameContainer.GetUIManager()->Render(render_state);

  m_FPSClock.Update();

  if(m_DrawFPS)
  {
    std::string fps_data = std::to_string(m_FPSClock.GetFrameCount());
    g_TextManager.SetTextPos(Vector2f(40, 40) - render_state.GetRenderSize() / 2.0f);
    g_TextManager.SetPrimaryColor();
    g_TextManager.SetShadowColor();
    g_TextManager.SetTextMode(TextRenderMode::kOutlined);
    g_TextManager.ClearTextBounds();
    g_TextManager.RenderText(fps_data.data(), -1, 1, render_state);
  }

  if(m_DrawProfileData)
  {
    RenderProfilerData(render_state);
  }
}

void GameClientUIManager::ShowQuitPopup()
{
  CancelPopup();

  auto & ui = GetUIManager();
  auto & game_interface = ui.CreateGameInterface();

  BIND_SCRIPT_INTERFACE(game_interface, this, Quit);
  BIND_SCRIPT_INTERFACE(game_interface, this, CancelPopup);

  ui.PushUIDef(g_QuitPopup);

  m_PopupOpen = true;
}

void GameClientUIManager::CancelPopup()
{
  GetUIManager().ClearUI();
  GetUIManager().ClearGameInterface();
  m_PopupOpen = false;
  m_ShopOpen = false;
}

void GameClientUIManager::ShowTutorial()
{
  auto & render_state = m_GameContainer.GetRenderState();
}

bool GameClientUIManager::IsPopupOpen()
{
  return m_PopupOpen || m_ShopOpen;
}

bool GameClientUIManager::IsBlocking()
{
  return GetUIManager().HasSelectedElement();
}

bool GameClientUIManager::WantsToQuit()
{
  return m_WantsToQuit;
}

UIManager & GameClientUIManager::GetUIManager()
{
  return *m_GameContainer.GetEngineState().GetUIManager();
}

void GameClientUIManager::AddNoiseAlert(float angle, float alpha)
{
  NoiseAlert alert;
  alert.angle = angle;
  alert.alpha = alpha;

  m_Alerts.push_back(alert);
}

GameClientUIData GameClientUIManager::GetScriptData()
{
  auto & game_state = m_GameContainer.GetInstanceData()->GetFullState();
  auto & global_data = game_state.m_InstanceData;
  auto & client_local = m_GameContainer.GetInstanceData()->GetClientLocalData(m_LocalIndex);
  auto & camera = m_GameContainer.GetClientSystems()->GetCamera();

  GameClientUIData data;

#ifdef NET_USE_ROUND_TIMER
  if(global_data.m_RoundState == RoundState::kPreRound || global_data.m_RoundState == RoundState::kRound)
  {
    static const bool kDisplayMinutes = true;
    if(kDisplayMinutes && global_data.m_RoundState != RoundState::kPreRound)
    {
      auto timer = global_data.m_RoundTimer / 60;
      auto minutes = timer / 60;
      auto seconds = timer % 60;

      char timer_str[20];
      snprintf(timer_str, sizeof(timer_str), "%d:%02d", minutes, seconds);

      data.timer = timer_str;
    }
    else
    {
      data.timer = std::to_string((global_data.m_RoundTimer / 60) + 1);
    }

    data.timer_scale = 1.0f - (global_data.m_RoundTimer % 60) / 60.0f;
    data.timer_pre_round = global_data.m_RoundState == RoundState::kPreRound;
  }
#endif

  data.alerts = m_Alerts;
  data.num_alerts = m_Alerts.size();

  data.max_ammo = kDefaultAmmo;


  if(client_local.m_PlayerIndex != -1)
  {
    auto player_obj = game_state.m_ServerEntityManager.GetReservedSlotEntityAs<PlayerServerEntity>(
            client_local.m_PlayerIndex);
    if (player_obj)
    {
      data.ammo = player_obj->m_Ammo;
      data.health = player_obj->m_Health;
      data.lives = player_obj->m_Lives;

      if(player_obj->m_Upgrades & (int)PlayerUpgrade::kAmmo1)
      {
        data.max_ammo += 6;
      }

      if(player_obj->m_Upgrades & (int)PlayerUpgrade::kAmmo2)
      {
        data.max_ammo += 6;
      }
    }
  }

  return data;
}

void GameClientUIManager::Quit()
{
  m_WantsToQuit = true;
}

void GameClientUIManager::BuyDamage()
{
  auto & game_state = m_GameContainer.GetInstanceData()->GetFullState();
  auto & global_data = game_state.m_InstanceData;
  auto & client_local = m_GameContainer.GetInstanceData()->GetClientLocalData(m_LocalIndex);
  auto & input_manager = m_GameContainer.GetClientSystems()->GetInputManager();

  if(client_local.m_PlayerIndex != -1)
  {
    auto player_obj = game_state.m_ServerEntityManager.GetReservedSlotEntityAs<PlayerServerEntity>(
            client_local.m_PlayerIndex);
    if (player_obj)
    {
      if(player_obj->m_Upgrades & (int)PlayerUpgrade::kDamage1)
      {
        m_GameContainer.GetInstanceData()->GetEventSender().SendClientEvent(PurchaseEvent{ClientNetworkEvent{}, (int)PlayerUpgrade::kDamage2});
      }
      else
      {
        m_GameContainer.GetInstanceData()->GetEventSender().SendClientEvent(PurchaseEvent{ClientNetworkEvent{}, (int)PlayerUpgrade::kDamage1});
      }
    }
  }

  m_RefreshShop = true;
}

void GameClientUIManager::BuyAmmo()
{
  auto & game_state = m_GameContainer.GetInstanceData()->GetFullState();
  auto & global_data = game_state.m_InstanceData;
  auto & client_local = m_GameContainer.GetInstanceData()->GetClientLocalData(m_LocalIndex);
  auto & input_manager = m_GameContainer.GetClientSystems()->GetInputManager();


  if(client_local.m_PlayerIndex != -1)
  {
    auto player_obj = game_state.m_ServerEntityManager.GetReservedSlotEntityAs<PlayerServerEntity>(
            client_local.m_PlayerIndex);
    if (player_obj)
    {
      if(player_obj->m_Upgrades & (int)PlayerUpgrade::kAmmo1)
      {
        m_GameContainer.GetInstanceData()->GetEventSender().SendClientEvent(PurchaseEvent{ClientNetworkEvent{}, (int)PlayerUpgrade::kAmmo2});
      }
      else
      {
        m_GameContainer.GetInstanceData()->GetEventSender().SendClientEvent(PurchaseEvent{ClientNetworkEvent{}, (int)PlayerUpgrade::kAmmo1});
      }
    }
  }

  m_RefreshShop = true;
}

void GameClientUIManager::BuyHealth()
{
  auto & game_state = m_GameContainer.GetInstanceData()->GetFullState();
  auto & global_data = game_state.m_InstanceData;
  auto & client_local = m_GameContainer.GetInstanceData()->GetClientLocalData(m_LocalIndex);
  auto & input_manager = m_GameContainer.GetClientSystems()->GetInputManager();


  if(client_local.m_PlayerIndex != -1)
  {
    auto player_obj = game_state.m_ServerEntityManager.GetReservedSlotEntityAs<PlayerServerEntity>(
            client_local.m_PlayerIndex);
    if (player_obj)
    {
      if(player_obj->m_Upgrades & (int)PlayerUpgrade::kHealth1)
      {
        m_GameContainer.GetInstanceData()->GetEventSender().SendClientEvent(PurchaseEvent{ClientNetworkEvent{}, (int)PlayerUpgrade::kHealth2});
      }
      else
      {
        m_GameContainer.GetInstanceData()->GetEventSender().SendClientEvent(PurchaseEvent{ClientNetworkEvent{}, (int)PlayerUpgrade::kHealth1});
      }
    }
  }

  m_RefreshShop = true;
}

void GameClientUIManager::BuySpeed()
{
  m_GameContainer.GetInstanceData()->GetEventSender().SendClientEvent(PurchaseEvent{ClientNetworkEvent{}, (int)PlayerUpgrade::kSpeed1}, 0);
}

void GameClientUIManager::BuyLife()
{
  auto & game_state = m_GameContainer.GetInstanceData()->GetFullState();
  auto & global_data = game_state.m_InstanceData;
  auto & client_local = m_GameContainer.GetInstanceData()->GetClientLocalData(m_LocalIndex);


  if(client_local.m_PlayerIndex != -1)
  {
    auto player_obj = game_state.m_ServerEntityManager.GetReservedSlotEntityAs<PlayerServerEntity>(
            client_local.m_PlayerIndex);
    if (player_obj)
    {
      if((player_obj->m_Upgrades & (int)PlayerUpgrade::kLife1) && (player_obj->m_Upgrades & (int)PlayerUpgrade::kLife2))
      {
        m_GameContainer.GetInstanceData()->GetEventSender().SendClientEvent(PurchaseEvent{ClientNetworkEvent{}, (int)PlayerUpgrade::kLife3});
      }
      else if(player_obj->m_Upgrades & (int)PlayerUpgrade::kLife1)
      {
        m_GameContainer.GetInstanceData()->GetEventSender().SendClientEvent(PurchaseEvent{ClientNetworkEvent{}, (int)PlayerUpgrade::kRate2});
      }
      else
      {
        m_GameContainer.GetInstanceData()->GetEventSender().SendClientEvent(PurchaseEvent{ClientNetworkEvent{}, (int)PlayerUpgrade::kRate1});
      }
    }
  }

  m_RefreshShop = true;
}

void GameClientUIManager::BuyRate()
{
  auto & game_state = m_GameContainer.GetInstanceData()->GetFullState();
  auto & global_data = game_state.m_InstanceData;
  auto & client_local = m_GameContainer.GetInstanceData()->GetClientLocalData(m_LocalIndex);


  if(client_local.m_PlayerIndex != -1)
  {
    auto player_obj = game_state.m_ServerEntityManager.GetReservedSlotEntityAs<PlayerServerEntity>(
            client_local.m_PlayerIndex);
    if (player_obj)
    {
      if(player_obj->m_Upgrades & (int)PlayerUpgrade::kRate1)
      {
        m_GameContainer.GetInstanceData()->GetEventSender().SendClientEvent(PurchaseEvent{ClientNetworkEvent{}, (int)PlayerUpgrade::kRate2});
      }
      else
      {
        m_GameContainer.GetInstanceData()->GetEventSender().SendClientEvent(PurchaseEvent{ClientNetworkEvent{}, (int)PlayerUpgrade::kRate1});
      }
    }
  }

  m_RefreshShop = true;
}