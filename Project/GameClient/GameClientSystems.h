#pragma once

#include "GameClient/GameCamera.h"
#include "Project/GameClient/Input/GameClientInputManager.h"
#include "Project/GameClient/UI/GameClientUIManager.h"
#include "Project/GameClient/Network/GameNetworkClient.h"

class GameContainer;

class GameClientSystems
{
public:
  GameClientSystems(GameContainer & container);
  ~GameClientSystems();

  GameClientInputManager & GetInputManager();
  GameClientUIManager & GetUIManager();

  GameCamera & GetCamera();

private:

  GameClientInputManager m_InputManager;
  GameClientUIManager m_UIManager;

  GameCamera m_Camera;
};
