
#include "GameShared/GameSharedCommon.h"
#include "GameShared/Systems/TargetDatabase.h"

#include "Game/ServerEntities/GameServerEntityBase.refl.h"
#include "Game/ServerEntities/Player/PlayerServerEntity.refl.h"

#include "Runtime/Collision/CollisionDatabase.h"

void TargetDatabase::PushTarget(NotNullPtr<GameServerEntityBase> obj, GameLogicContainer & game_container)
{
  TargetData target_data;
  target_data.m_Handle = obj->GetEntityHandle();
  target_data.m_Position = obj->m_Position;
  target_data.m_Team = -1;

  auto player = obj->CastTo<PlayerServerEntity>();
  if(player)
  {
    auto player_info = game_container.GetLowFrequencyInstanceData().m_Players.TryGet(player->GetSlotIndex());
    if(player_info)
    {
      target_data.m_Team = player_info->m_Team;
    }
  }

  m_Data.emplace_back(target_data);
}

std::vector<ServerEntityHandle> TargetDatabase::QueryForTargets(NotNullPtr<GameServerEntityBase> src, GameNetVal vision_cone_angle,
        GameNetVal vision_distance, const GameNetVec2 & vision_forward, uint32_t collision_mask,
        NullOptPtr<CollisionDatabase> collision_database, GameLogicContainer & game_container)
{
  std::vector<ServerEntityHandle> targets;

  int team = -1;
  auto player = src->CastTo<PlayerServerEntity>();
  if(player)
  {
    auto player_info = game_container.GetLowFrequencyInstanceData().m_Players.TryGet(player->GetSlotIndex());
    if(player_info)
    {
      team = player_info->m_Team;
    }
  }

  auto cos_angle = GameNetLUT::Cos(vision_cone_angle);

  for(auto & target : m_Data)
  {
    if(team != -1 && target.m_Team == team)
    {
      continue;
    }

    auto mdist = ManhattanDist(target.m_Position, src->m_Position);
    if(vision_distance < GameNetVal(mdist))
    {
      continue;
    }

    auto dist = IntersectionVecFuncs<GameNetVec2>::Dist(target.m_Position, src->m_Position);
    if(dist == GameNetVal(0))
    {
      targets.push_back(target.m_Handle);
      continue;
    }

    if(dist > vision_distance)
    {
      continue;
    }

    auto offset = target.m_Position - src->m_Position;
    offset.x /= dist;
    offset.y /= dist;

    auto dot = IntersectionVecFuncs<GameNetVec2>::Dot(offset, vision_forward);
    if(cos_angle > dot)
    {
      continue;
    }

    if(collision_database == nullptr)
    {
      targets.push_back(target.m_Handle);
      continue;
    }

    auto collision = collision_database->CheckLineOfSight(src->m_Position, target.m_Position, collision_mask);
    if(collision == 0)
    {
      targets.push_back(target.m_Handle);
    }
  }

  return targets;
}

void TargetDatabase::Clear()
{
  m_Data.clear();
}
