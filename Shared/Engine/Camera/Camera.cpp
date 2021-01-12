
#include "Engine/EngineCommon.h"
#include "Engine/Camera/Camera.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Rendering/RenderSettings.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/DrawList/DrawList.h"
#include "Engine/Entity/ClientEntitySystem.h"
#include "Engine/Map/MapSystem.h"
#include "Engine/VisualEffect/VisualEffectManager.h"
#include "Engine/EngineState.h"
#include "Engine/Profiler/Profiler.h"

Camera::Camera(const Vector2 & game_resolution, const Box & viewport, const RenderVec2 & initial_position) :
  m_GameResolution(game_resolution), m_Viewport(viewport), m_Position(initial_position)
{

}

void Camera::SetGameResolution(const RenderVec2 & resolution)
{
  m_GameResolution = resolution;
}

void Camera::SetViewport(const Box & viewport)
{
  m_Viewport = viewport;
}

void Camera::SetPosition(const RenderVec2 & position)
{
  m_Position = position;
}

RenderVec2 Camera::FinalizePosition(const RenderVec2 & target_position)
{
  return target_position;
}

void Camera::BootstrapShader(ShaderProgram & shader, RenderState & render_state)
{
  render_state.BindShader(shader);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), render_state.GetShaderScreenSizeValue());
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 255));
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), 1.0f, 0.0f, 0.0f, 1.0f);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), -m_FinalPosition);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);
}

const RenderVec2 & Camera::GetGameResolution() const
{
  return m_GameResolution;
}

const Box & Camera::GetViewport() const
{
  return m_Viewport;
}

const RenderVec2 & Camera::GetPosition() const
{
  return m_Position;
}

RenderVec2 Camera::GetViewportSize() const
{
  return RenderVec2(m_Viewport.Size());
}

RenderVec2 Camera::TransformFromScreenSpaceToClipSpace(const RenderVec2 & pos)
{
  auto offset_pos = pos - RenderVec2{ m_Viewport.m_Start };
  RenderVec2 screen_size = GetViewportSize();
  auto transformed_pos = offset_pos;
  transformed_pos -= screen_size * 0.5f;

  transformed_pos /= screen_size * 0.5f;
  return transformed_pos;
}

RenderVec2 Camera::TransformFromScreenSpaceToWorldSpace(const RenderVec2 & pos)
{
  auto clip_pos = TransformFromScreenSpaceToClipSpace(pos);
  return TransformFromClipSpaceToWorldSpace(clip_pos);
}

RenderVec2 Camera::TransformFromClipSpaceToWorldSpace(const RenderVec2 & pos)
{
  auto transformed_pos = pos;
  transformed_pos *= m_GameResolution * 0.5f;
  transformed_pos += m_Position;
  return transformed_pos;
}

void Camera::Draw(GameContainer & game_container, NotNullPtr<EngineState> engine_state, RenderState & render_state)
{
  Box game_viewport;

  m_FinalPosition = FinalizePosition(m_Position);

  render_state.EnableBlendMode();

  game_viewport.m_Start = m_FinalPosition - (m_GameResolution / 2.0f);
  game_viewport.m_End = game_viewport.m_Start + m_GameResolution;

  auto visitor = [&](ShaderProgram & shader)
  {
    render_state.BindShader(shader);
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), RenderVec4(m_GameResolution, GetViewportSize()));
  };

  g_ShaderManager.VisitShaders(visitor);

  DrawList draw_list;
  engine_state->GetMapSystem()->DrawAllMaps(game_viewport, draw_list);
  engine_state->GetEntitySystem()->DrawAllEntities(game_viewport, draw_list);
  engine_state->GetVisualEffectManager()->DrawAllEffects(game_viewport, draw_list);
  draw_list.Draw(game_container, game_viewport, m_FinalPosition, render_state);
}


