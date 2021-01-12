

#include "GameProject/GameCommon.h"

#include "Project/GameServerFramework/GameServerWorld.h"

#include "GameProject/GameServerEventSender.h"
#include "GameProject/GameStage.h"
#include "GameProject/GameCollisionType.refl.h"

#include "GameProject/ServerEntities/GameServerEntityBase.refl.h"
#include "GameProject/ServerEntities/GameServerEntityBase.refl.meta.h"
#include "GameServerEntityBase.refl.h"


CLIENT_ASSET(ClientAssetType::kEntity, "./Gameplay/DefaultServerObject.entity", g_DefaultServerObjectEntity);

SpritePtr g_DefaultEmptrySpritePtr;

void GameServerEntityBase::Init(const GameServerEntityBaseInitData & init_data, GameServerWorld & game_world)
{
  
}

void GameServerEntityBase::UpdateFirst(GameServerWorld & container)
{
  m_CollisionId.Clear();
  container.GetSystems().GetCollisionDatabase().GetCollisionId(m_CollisionId);
}

void GameServerEntityBase::InitPosition(const Vector2 & pos)
{
  m_Position = GameNetVec2(pos.x, pos.y);
}

GameNetVec2 GameServerEntityBase::GetPosition() const
{
  return m_Position;
}

void GameServerEntityBase::SetPosition(const GameNetVec2 & pos)
{
  m_Position = pos;
}

Optional<AnimationState> GameServerEntityBase::GetAnimationState() const
{
  return {};
}

void GameServerEntityBase::SetAnimationState(const AnimationState & anim_state)
{

}

void GameServerEntityBase::SetAssociatedPlayer(int associated_player) const
{

}

bool GameServerEntityBase::FrameAdvance(uint32_t anim_name_hash, bool loop, int frames)
{
  auto anim_state = GetAnimationState();
  auto & sprite = GetSprite();
  if (anim_state && sprite.IsLoaded())
  {
    bool result = sprite->FrameAdvance(anim_name_hash, anim_state.Value(), loop, frames);
    SetAnimationState(anim_state.Value());

    return result;
  }

  return false;
}

void GameServerEntityBase::ResetAnimState()
{
  SetAnimationState(AnimationState{});
}

Optional<Box> GameServerEntityBase::GetMoveBox(uint32_t box_name_hash)
{
  auto & sprite = GetSprite();
  if(sprite)
  {
    auto box = sprite->GetSingleBoxDefault(box_name_hash).Offset(m_Position);
    return box;
  }

  return {};
}

void GameServerEntityBase::PushDealDamageEventBox(const Box & b, const DamageEvent & damage_event, GameServerWorld & game_world)
{
  EventMetaData new_meta(this, &game_container);

  auto facing = GetFacing();

  Box box = b;
  if (facing && facing.Value() == CharacterFacing ::kLeft)
  {
    box = box.MirrorX();
  }

  box = box.Offset(m_Position);

  auto dmg = game_container.GetServerObjectEventSystem().PushEventSource<DamageEvent>(box, new_meta);
  *dmg = damage_event;
}

void GameServerEntityBase::PushDealDamageEventBoxes(uint32_t multi_box_name_hash, const DamageEvent & damage_event, GameServerWorld & game_world)
{
  auto & sprite = GetSprite();
  auto animation_state = GetAnimationState();
  if(sprite && animation_state)
  {
    auto frame_id = sprite->GetAnimationFrameId(animation_state->m_AnimIndex, animation_state->m_AnimFrame);

    auto boxes = sprite->GetMultiBox(multi_box_name_hash, frame_id);
    for (auto &box : boxes)
    {
      PushReceiveDamageEventBox(box, game_container);
    }
  }
}

void GameServerEntityBase::PushDealDamageEventBox(uint32_t box_name_hash, const DamageEvent & damage_event, GameServerWorld & game_world)
{
  auto & sprite = GetSprite();
  if(sprite)
  {
    auto box = sprite->GetSingleBoxDefault(box_name_hash).Offset(m_Position);
    PushDealDamageEventBox(box, damage_event, game_container);
  }
}

void GameServerEntityBase::PushReceiveDamageEventBox(const Box & b, GameServerWorld & game_world)
{
  auto facing = GetFacing();

  Box box = b;
  if (facing && facing.Value() == CharacterFacing::kLeft)
  {
    box = box.MirrorX();
  }

  box = box.Offset(m_Position);
  game_container.GetServerObjectEventSystem().PushEventReceiver<DamageEvent>(GetEntityHandle(), box);
}

void GameServerEntityBase::PushReceiveDamageEventBox(uint32_t box_name_hash, GameServerWorld & game_world)
{
  auto & sprite = GetSprite();
  if(sprite)
  {
    auto box = sprite->GetSingleBoxDefault(box_name_hash).Offset(m_Position);
    PushReceiveDamageEventBox(box, game_container);
  }
}

void GameServerEntityBase::PushReceiveDamageEventBoxes(uint32_t multi_box_name_hash, GameServerWorld & game_world)
{
  auto & sprite = GetSprite();
  auto animation_state = GetAnimationState();
  if(sprite && animation_state)
  {
    auto frame_id = sprite->GetAnimationFrameId(animation_state->m_AnimIndex, animation_state->m_AnimFrame);

    auto boxes = sprite->GetMultiBox(multi_box_name_hash, frame_id);
    for (auto &box : boxes)
    {
      PushReceiveDamageEventBox(box, game_container);
    }
  }
}

void GameServerEntityBase::PushReceiveDamageCollisionBox(const Box & b, GameServerWorld & game_world)
{
  game_container.GetSystems().GetCollisionDatabase().PushDynamicCollision(b.Offset(m_Position),
          (uint32_t)GameCollisionType::kCollisionDamagable, CollisionDatabaseObjectInfo(GetEntityHandle()), m_CollisionId);
}

void GameServerEntityBase::PushReceiveDamageCollisionBox(uint32_t box_name_hash, GameServerWorld & game_world)
{
  auto & sprite = GetSprite();
  if(sprite)
  {
    auto box = sprite->GetSingleBoxDefault(box_name_hash).Offset(m_Position);
    PushReceiveDamageCollisionBox(box, game_container);
  }
}

void GameServerEntityBase::PushReceiveDamageCollisionBoxes(uint32_t multi_box_name_hash, GameServerWorld & game_world)
{
  auto & sprite = GetSprite();
  auto animation_state = GetAnimationState();
  if(sprite && animation_state)
  {
    auto frame_id = sprite->GetAnimationFrameId(animation_state->m_AnimIndex, animation_state->m_AnimFrame);

    auto boxes = sprite->GetMultiBox(multi_box_name_hash, frame_id);
    for (auto &box : boxes)
    {
      PushReceiveDamageCollisionBox(box, game_container);
    }
  }
}

void GameServerEntityBase::PushCVCBox(const Box & b, GameServerWorld & game_world)
{
  game_container.GetSystems().GetCVCPushSystem().SetCharacterCVCPosition(b, this);
}

void GameServerEntityBase::PushCVCBox(uint32_t box_name_hash, GameServerWorld &game_container)
{
  auto & sprite = GetSprite();
  if(sprite)
  {
    auto box = sprite->GetSingleBoxDefault(box_name_hash).Offset(m_Position);
    PushCVCBox(box, game_container);
  }
}

void GameServerEntityBase::PushSelfAsTarget(GameServerWorld & game_world)
{
  game_container.GetSystems().GetTargetDatabase().PushTarget(this, game_container);
}

const SpritePtr & GameServerEntityBase::GetSprite() const
{
  return g_DefaultEmptrySpritePtr;
}

Optional<CharacterFacing> GameServerEntityBase::GetFacing() const
{
  return {};
}


Optional<int> GameServerEntityBase::GetCollisionId() const
{
  return m_CollisionId;
}

#ifdef MOVER_ONE_WAY_COLLISION
MoverResult GameServerEntityBase::MoveCheckCollisionDatabase(GameServerWorld & game_world, const GameNetVec2 & velocity, bool fallthrough)
#else
MoverResult GameServerEntityBase::MoveCheckCollisionDatabase(GameServerWorld & game_world, const GameNetVec2 & velocity)
#endif
{
  auto & stage = game_container.GetStage();
  auto & collision = game_container.GetSystems().GetCollisionDatabase();

  auto & sprite = GetSprite();
  auto move_box = sprite->GetSingleBoxDefault(COMPILE_TIME_CRC32_STR("MoveBox"));

  MoveRequest req = Mover::CreateMoveRequest(m_Position, velocity, move_box);

#ifdef MOVER_ONE_WAY_COLLISION
  auto result = Mover::UpdateMover(collision, req, (int)GameCollisionType::kCollisionSolid,
          fallthrough ? 0 : (int)GameCollisionType::kCollisionOneWay);
#else
  auto result = Mover::UpdateMover(collision, req, 0xFFFFFFFF);
#endif

  if (result.m_HitRight)
  {
    m_Position.x = IntersectionFuncs<GameNetVal>::NextLowest(result.m_ResultPos.x + 1);
  }
  else if (result.m_HitLeft)
  {
    m_Position.x = result.m_ResultPos.x;
  }
  else
  {
    m_Position.x += velocity.x;
  }

  if (result.m_HitTop)
  {
    m_Position.y = IntersectionFuncs<GameNetVal>::NextLowest(result.m_ResultPos.y + 1);
  }
  else if (result.m_HitBottom)
  {
    m_Position.y = result.m_ResultPos.y;
  }
  else
  {
    m_Position.y += velocity.y;
  }

  return result;
}

GameNetVec2 GameServerEntityBase::MoveCheckIntersectionDatabase(GameServerWorld & game_world, const GameNetVec2 & vel, GameNetVal player_radius, GameNetVal move_threshold)
{
  GameNetVal one = GameNetVal(1);
  GameNetVal two = GameNetVal(2);

  auto & stage = game_container.GetStage();
  auto & collision = stage.GetIntersectionDatabase();

  auto result_velocity = vel;
  auto velocity = vel;

  Intersection<GameNetVal>::CollisionLine movement(m_Position, m_Position + velocity);
  IntersectionResult<GameNetVal> result;
  CollisionDatabaseData<GameNetVal> hit_line;

  if (collision.SweptCircleTest(movement, player_radius, result, hit_line, 0x01) == false)
  {
    m_Position += velocity;
  }
  else
  {
    if (result.m_T > move_threshold)
    {
      result.m_T -= move_threshold;

      auto actual_movement = velocity * result.m_T;
      m_Position += actual_movement;

      velocity -= actual_movement;
    }

    auto reflect_dp = IntersectionVecFuncs<GameNetVec2>::Dot(result.m_HitNormal, result_velocity);
    result_velocity -= result.m_HitNormal * reflect_dp * two;

    auto second_check_dp = IntersectionVecFuncs<GameNetVec2>::Dot(result.m_HitNormal, velocity);
    velocity -= result.m_HitNormal * second_check_dp * two;

    Intersection<GameNetVal>::CollisionLine new_movement(m_Position, m_Position + velocity);
    if (collision.SweptCircleTest(new_movement, player_radius, result, hit_line, 0x01) == false)
    {
      m_Position += velocity;
    }
  }

  return result_velocity;
}

std::vector<ServerEntityHandle> GameServerEntityBase::QueryTargetDatabase(GameNetVal vision_cone_angle,
        GameNetVal vision_distance, const GameNetVec2 & vision_forward, uint32_t collision_mask,
        GameServerWorld & game_world)
{
  auto coll_database = collision_mask != 0 ? &game_container.GetSystems().GetCollisionDatabase() : nullptr;

  return game_container.GetSystems().GetTargetDatabase().QueryForTargets(this, vision_cone_angle,
          vision_distance, vision_forward, collision_mask, coll_database, game_container);
}
