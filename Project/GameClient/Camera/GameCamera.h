#pragma once

#include "Engine/Camera/Camera.h"

class GameContainer;

static const int kDefaultResolutionWidth = 420;
static const int kDefaultResolutionHeight = 240;

#define CAMERA_FOLLOW_PLAYER

struct CameraShakeInfo
{
  float m_StartTime;
  float m_Duration;
  float m_Amplitude;
  float m_Frequency;

  std::unique_ptr<float[]> m_Samples;
  int m_NumSamples;
};

class GameCamera : public Camera
{
public:
  GameCamera(GameContainer & container);

  virtual RenderVec2 FinalizePosition(const RenderVec2 & target_position) override;

  void TransformWorldSpaceToGameplaySpace(int & x, int & y);
  Vector2 TransformWorldSpaceToGameplaySpace(const Vector2 & vec);
  Box TransformWorldSpaceToGameplaySpace(const Box & box);

  void Shake(float duration, float amplitude, float frequency = 60.0f);

protected:

  RenderVec2 EvalShake(const CameraShakeInfo & shake_info, float t);

private:

  GameContainer & m_GameContainer;

  std::vector<CameraShakeInfo> m_ShakeInfo;
};

