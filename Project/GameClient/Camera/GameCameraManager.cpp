
#include "GameClient/GameClientCommon.h"
#include "GameClient/GameContainer.h"
#include "GameClient/Camera/GameCamera.h"
#include "GameClient/Camera/GameCameraManager.h"

#include "Engine/EngineState.h"
#include "Engine/Window/Window.h"

static float g_SplitScreenCameraExtents[kMaxLocalPlayers][kMaxLocalPlayers][4] =
  {
    {
      { 0.0f, 0.0f, 1.0f, 1.0f },
    },
    {
      { 0.0f, 0.0f, 1.0f, 0.5f },
      { 0.0f, 0.5f, 1.0f, 1.0f }
    },
    {
      { 0.0f, 0.0f, 0.5f, 0.5f },
      { 0.5f, 0.0f, 1.0f, 0.5f },
      { 0.0f, 0.5f, 1.0f, 1.0f }
    },
    {
      { 0.0f, 0.0f, 0.5f, 0.5f },
      { 0.5f, 0.0f, 1.0f, 0.5f },
      { 0.0f, 0.5f, 0.5f, 1.0f },
      { 0.5f, 0.5f, 1.0f, 1.0f }
    }
  };

static_assert(kMaxLocalPlayers <= 4, "g_SplitScreenCameraExtents needs to be updated if more local players are allowed");

GameCameraManager::GameCameraManager(GameContainer & container) :
  m_GameContainer(container),
  m_Cameras(kMaxLocalPlayers)
{

}

GameCameraHandle GameCameraManager::CreateCamera()
{
  ASSERT(m_Cameras.GetNumHandles() < kMaxLocalPlayers);
  auto handle = m_Cameras.AllocateElem(m_GameContainer);
  UpdateViewports();
  return handle;
}

void GameCameraManager::DestroyCamera(const GameCameraHandle & handle)
{
  m_Cameras.FreeElem(handle);
  UpdateViewports();
}

NullOptPtr<GameCamera> GameCameraManager::GetCamera(const GameCameraHandle & handle)
{
  return m_Cameras.Resolve(handle);
}

void GameCameraManager::DrawAll(NotNullPtr<EngineState> engine_state, RenderState & render_state)
{
  // Do this now in case the window size has changed
  UpdateViewports();

  m_Cameras.VisitEach([&](GameCamera & camera)
  {
    camera.Draw(m_GameContainer, engine_state, render_state);
  });
}

void GameCameraManager::UpdateViewports()
{
  // Sort out viewports for each camera
  auto num_viewports = m_Cameras.GetNumHandles();
  auto window_resolution = m_GameContainer.GetWindow().GetSize();

  int viewport_index = 0;
  m_Cameras.VisitEach([&](GameCamera & camera)
  {
    Vector2 viewport_start = { static_cast<float>(window_resolution.x) * g_SplitScreenCameraExtents[num_viewports][viewport_index][0],
                               static_cast<float>(window_resolution.y) * g_SplitScreenCameraExtents[num_viewports][viewport_index][1] };
    Vector2 viewport_end   = { static_cast<float>(window_resolution.x) * g_SplitScreenCameraExtents[num_viewports][viewport_index][2],
                               static_cast<float>(window_resolution.y) * g_SplitScreenCameraExtents[num_viewports][viewport_index][3] };
    camera.SetViewport(Box { viewport_start, viewport_end });

    viewport_index++;
  });
}
