
#pragma once

#include "Foundation/Common.h"
#include "Runtime/ClientComponent/ClientComponentInitData.refl.h"
#include "Runtime/Animation/AnimationState.h"
#include "Engine/ClientComponent/ClientComponent.h"

class RenderState;
class PlayerServerEntity;

struct PlayerServerEntityInfo
{
  NotNullPtr<PlayerServerEntity> m_CurrentObject;
  bool m_IsLocal;
  int m_LocalIndex;
  Vector2f m_CurrentPos;
};

struct PlayerComponentInitData : public ClientComponentInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION(PlayerComponentInitData);
};

class PlayerComponent : public ClientComponent
{
public:
  DECLARE_CLIENT_COMPONENT;

  PlayerComponent(PlayerComponentInitData && init_data);
  virtual ~PlayerComponent();

  virtual void OnActivate() override;
  virtual void OnDestroy() override;
  virtual void ServerUpdate() override;
  virtual void ServerDestroy() override;

  void UpdateFirst();

  void Draw(const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state);

  PlayerServerEntityInfo GetServerObjectInfo();

  static Color GetTeamColor(int team);
  static Color GetTeamDarkColor(int team);

private:


  RenderVec2 m_DeadReckonOffset;
  RenderVec2 m_DeadReckonDec;
  RenderVec2 m_DeadReckonPos;

  int m_LastFrame;
};
