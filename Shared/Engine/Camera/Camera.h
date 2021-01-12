#pragma once

#include "Foundation/Common.h"

class GameContainer;
class EngineState;
class RenderState;
class ShaderProgram;

class Camera
{
public:
  Camera(const Vector2 & game_resolution = {}, const Box& viewport = {}, const RenderVec2 & initial_position = {});

  void SetGameResolution(const RenderVec2 & resolution);
  void SetViewport(const Box & viewport);
  void SetPosition(const RenderVec2 & position);

  virtual RenderVec2 FinalizePosition(const RenderVec2 & target_position);

  void BootstrapShader(ShaderProgram & shader, RenderState & render_state);

  const RenderVec2 & GetGameResolution() const;
  const Box & GetViewport() const;
  const RenderVec2 & GetPosition() const;

  RenderVec2 GetViewportSize() const;

  RenderVec2 TransformFromScreenSpaceToClipSpace(const RenderVec2 & pos);
  RenderVec2 TransformFromScreenSpaceToWorldSpace(const RenderVec2 & pos);
  RenderVec2 TransformFromClipSpaceToWorldSpace(const RenderVec2 & pos);

  void Draw(GameContainer & game_container, NotNullPtr<EngineState> engine_state, RenderState & render_state);

private:
  RenderVec2 m_GameResolution;
  RenderVec2 m_Position;
  RenderVec2 m_FinalPosition;

  Box m_Viewport;
};
