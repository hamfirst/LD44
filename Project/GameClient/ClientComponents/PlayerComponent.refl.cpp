
#include "GameClient/GameClientCommon.h"

#include "Engine/Entity/ClientEntity.h"
#include "Engine/Entity/ClientEntitySystem.h"
#include "Engine/Audio/AudioManager.h"

#include "GameProject/ServerEntities/Player/PlayerServerEntity.refl.meta.h"

#include "GameClient/GameContainer.h"
#include "GameClient/ClientComponents/PlayerComponent.refl.h"
#include "GameClient/ClientComponents/PlayerComponent.refl.meta.h"

#include "Engine/Rendering/GeometryVertexBufferBuilder.h"
#include "Engine/Shader/ShaderManager.h"

PlayerComponent::PlayerComponent(PlayerComponentInitData && init_data)
{
  m_DeadReckonOffset = {};
  m_DeadReckonDec = {};
  m_DeadReckonPos = {};

  m_LastFrame = -1;
}

PlayerComponent::~PlayerComponent()
{

}

void PlayerComponent::OnActivate()
{
  auto server_obj = GetEntity()->GetServerObjectAs<PlayerServerEntity>();
  m_DeadReckonPos = Vector2f(server_obj->m_Position.x, server_obj->m_Position.y);

  if (m_DeadReckonPos.x > 0)
  {
    GetEntity()->SetRotation(true, false);
  }

  GetEntity()->SetCustomDrawingCallback(EntityCustomDraw(&PlayerComponent::Draw, this));
}

void PlayerComponent::OnDestroy()
{

}

void PlayerComponent::ServerUpdate()
{
  auto info = GetServerObjectInfo();
  if(info.m_CurrentObject == nullptr)
  {
    return;
  }
  
  m_DeadReckonOffset = m_DeadReckonPos + m_DeadReckonOffset - info.m_CurrentPos;
  m_DeadReckonDec = m_DeadReckonOffset / (float)NET_SYNC_SERVER_RATE / 2.0f;
  m_DeadReckonPos = info.m_CurrentPos;
}

void PlayerComponent::ServerDestroy()
{

}

void PlayerComponent::UpdateFirst()
{
  auto info = GetServerObjectInfo();
  if(info.m_CurrentObject == nullptr)
  {
    return;
  }

  PlayerServerEntity * object;

  if (info.m_IsLocal)
  {
    object = info.m_CurrentObject;
    GetEntity()->SetPosition((Vector2)(info.m_CurrentPos));
  }
  else
  {
    object = info.m_CurrentObject;
    GetEntity()->SetPosition((Vector2)(info.m_CurrentPos + m_DeadReckonOffset));
    m_DeadReckonPos = info.m_CurrentPos;
    m_DeadReckonOffset -= m_DeadReckonDec;
  }

  auto & sprite = GetEntity()->GetSprite();
  auto & render_state = GetEntity()->GetRenderState();

  render_state.m_AnimIndex = object->m_AnimIndex;
  render_state.m_AnimFrame = object->m_AnimFrame;
  render_state.m_AnimDelay = object->m_AnimDelay;

#if defined(NET_USE_AIM_DIRECTION)

  GameNetVal aim_x = GameNetLUT::Cos(object->m_Input.m_AimDirection);

  if(aim_x > GameNetVal(0))
  {
    render_state.m_Matrix.x = 1.0f;
  }
  else
  {
    render_state.m_Matrix.x = -1.0f;
  }

#else
  if (object->m_Facing == CharacterFacing::kLeft)
  {
    render_state.m_Matrix.x = -1.0f;
  }
  else if (object->m_Facing == CharacterFacing::kRight)
  {
    render_state.m_Matrix.x = 1.0f;
  }
#endif

#ifdef CAMERA_FOLLOW_PLAYER
  if(info.m_LocalIndex != -1)
  {
    auto & camera = GetEntity()->GetGameContainer()->GetClientSystems()->GetCamera();
    camera.SetPosition(GetEntity()->GetPosition() - Vector2f(0, 4));
  }
#endif

  sprite->SendEventsTo(*GetEntity(), render_state, EventMetaData(GetEntity()->GetGameContainer()));
}

void PlayerComponent::Draw(const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state)
{
  auto info = GetServerObjectInfo();
  if(info.m_CurrentObject == nullptr)
  {
    return;
  }

  auto instance_data = GetEntity()->GetGameContainer()->GetInstanceData();
  if(instance_data == nullptr)
  {
    return;
  }

  if(instance_data->GetGlobalInstanceData().m_RoundState == RoundState::kPreRound &&
      instance_data->GetGlobalInstanceData().m_RoundTimer > kPreRoundTimer - 50)
  {
    return;
  }

  if(info.m_CurrentObject->m_FrozenFrames > 10)
  {
    return;
  }

  float aim_angle = 0;

  auto slot_index = info.m_CurrentObject->GetSlotIndex();
  auto player = instance_data->GetLowFrequencyData().m_Players.TryGet(slot_index);
  auto entity_pos = GetEntity()->GetPosition();

  auto draw_pos = Vector2(entity_pos - screen_center);

  if(info.m_CurrentObject->m_Bat == false)
  {
    auto text_len = g_TextManager.GetTextSize(player->m_UserName, 100, 1.0f);
    g_TextManager.SetTextPos(draw_pos + Vector2(text_len.Size().x / -2, 10));
    g_TextManager.SetPrimaryColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
    g_TextManager.SetShadowColor(Color(0, 0, 0, 0));
    g_TextManager.SetTextMode(TextRenderMode::kOutlined);
    g_TextManager.ClearTextBounds();
    g_TextManager.RenderText(player->m_UserName, 100, 1.0f, render_state);
  }

  aim_angle = (float)info.m_CurrentObject->m_Input.m_AimDirection;


  // Vampire
  float c = cosf(aim_angle), s = sinf(aim_angle);

  auto angle_normalized = (aim_angle / k2Pi);
  angle_normalized -= floorf(angle_normalized);

  auto anim_frame = (int)(angle_normalized * 16.0f + 0.5f) % 16;

  auto & sprite = GetEntity()->GetSprite();

  EntityRenderState gun_state;
  sprite->SyncFrameData(sprite->GetAnimationIndex(COMPILE_TIME_CRC32_STR("Gun")), anim_frame, 0, gun_state);

  auto gun_offset = Vector2f((c * 5), (s * 3) - 4);

  if(s > 0 && info.m_CurrentObject->m_Bat == false)
  {
    sprite->Render(render_state, gun_state, GetEntity()->GetPosition() + gun_offset - screen_center);
  }

  GetEntity()->GetGameContainer()->GetEngineState().GetEntitySystem()->DefaultDrawEntity(
          GetEntity(), viewport_bounds, screen_center, render_state, g_ShaderManager.GetDefaultWorldSpaceShader());

  if(s <= 0 && info.m_CurrentObject->m_Bat == false)
  {
    sprite->Render(render_state, gun_state, GetEntity()->GetPosition() + gun_offset - screen_center);
  }
}

PlayerServerEntityInfo PlayerComponent::GetServerObjectInfo()
{
  PlayerServerEntityInfo info;
  info.m_CurrentObject = GetEntity()->GetServerObjectAs<PlayerServerEntity>();

  if(info.m_CurrentObject == nullptr)
  {
    return {};
  }

  info.m_CurrentPos = Vector2f(info.m_CurrentObject->m_Position.x, info.m_CurrentObject->m_Position.y);

  auto instance_data = GetEntity()->GetGameContainer()->GetInstanceData();
  auto slot_index = info.m_CurrentObject->GetSlotIndex();

  auto player = instance_data->GetLowFrequencyData().m_Players.TryGet(slot_index);
  info.m_IsLocal = instance_data->GetGlobalInstanceData().m_AIPlayerInfo.HasAt(slot_index);
  info.m_LocalIndex = -1;

  auto num_local = instance_data->GetNumLocalData();
  for (int index = 0; index < num_local; ++index)
  {
    if (instance_data->GetClientLocalData(index).m_PlayerIndex == info.m_CurrentObject->GetSlotIndex())
    {
      info.m_IsLocal = true;
      info.m_LocalIndex = index;
      break;
    }
  }

  return info;
}

Color PlayerComponent::GetTeamColor(int team)
{
  switch (team)
  {
  case 0:
  default:
    return Color(177, 37, 25);
  case 1:
    return Color(63, 70, 192);
  case 2:
    return Color(54, 191, 42);
  case 3:
    return Color(62, 63, 62);
  }
}

Color PlayerComponent::GetTeamDarkColor(int team)
{
  switch (team)
  {
    case 0:
    default:
      return Color(140, 37, 25);
    case 1:
      return Color(63, 70, 160);
    case 2:
      return Color(54, 161, 42);
    case 3:
      return Color(41, 42, 41);
  }
}
