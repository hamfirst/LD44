
#pragma once

#include "Foundation/Common.h"
#include "Foundation/Handle/Handle.h"
#include "Foundation/Handle/HandleList.h"

class GameContainer;
class GameCamera;

using GameCameraHandle = SpecificHandle<GameCamera>;

class GameCameraManager
{
public:
  GameCameraManager(GameContainer & container);

  GameCameraHandle CreateCamera();
  void DestroyCamera(const GameCameraHandle & handle);

  NullOptPtr<GameCamera> GetCamera(const GameCameraHandle & handle);

  void DrawAll(NotNullPtr<EngineState> engine_state, RenderState & render_state);

private:

  void UpdateViewports();

private:

  GameContainer & m_GameContainer;

  HandleList<GameCamera> m_Cameras;
};

