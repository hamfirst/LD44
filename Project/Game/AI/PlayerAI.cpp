
#include "Game/GameCommon.h"
#include "Game/AI/PlayerAI.h"
#include "Game/GameStage.h"
#include "GameShared/Systems/GameLogicSystems.h"
#include "GameShared/Systems/TargetDatabase.h"
#include "Game/ServerEntities/Player/PlayerServerEntity.refl.h"

#include "Runtime/ServerEntity/ServerEntityManager.h"

static GameNetVal kBallRadius = GameNetVal("7");

auto kRandDashAngleMax = GameNetVal("0.2");
auto kRandDashAngleMin = GameNetVal(-kRandDashAngleMax);

void PlayerAI::InitAI(GameServerWorld & game, std::size_t player_index)
{
  auto & ai_info = game.GetInstanceData().m_AIPlayerInfo[player_index];
  auto player_obj = game.GetObjectManager().GetReservedSlotEntityAs<PlayerServerEntity>(player_index);
}

void PlayerAI::UpdateAI(GameServerWorld & game, std::size_t player_index)
{
  auto & player_info = game.GetLowFrequencyInstanceData().m_Players[player_index];
  auto & ai_info = game.GetInstanceData().m_AIPlayerInfo[player_index];
  auto & stage = game.GetStage();
  auto & targeting = game.GetSystems().GetTargetDatabase();
  auto & collision = game.GetSystems().GetCollisionDatabase();
  auto player_obj = game.GetObjectManager().GetReservedSlotEntityAs<PlayerServerEntity>(player_index);

  if (player_obj == nullptr)
  {
    return;
  }

  if(player_obj->GetSlotIndex() != 2)
  {
    return;
  }

  player_obj->m_Input.m_InputStr = GameNetVal(0);

  if(game.GetInstanceData().m_RoundState == RoundState::kPostRound)
  {
    if(game.GetInstanceData().m_RoundTimer == 60)
    {
      player_obj->PurchaseUpgrade(PlayerUpgrade::kHealth1);
      player_obj->PurchaseUpgrade(PlayerUpgrade::kDamage1);
      player_obj->PurchaseUpgrade(PlayerUpgrade::kDamage2);
      player_obj->PurchaseUpgrade(PlayerUpgrade::kAmmo1);
      player_obj->PurchaseUpgrade(PlayerUpgrade::kAmmo2);
      player_obj->PurchaseUpgrade(PlayerUpgrade::kLife1);
    }
  }
  else if(game.GetInstanceData().m_RoundState == RoundState::kRound)
  {
    if(game.GetInstanceData().m_FrameCount % 5 == 0)
    {
      player_obj->Use(game);
    }

    player_obj->m_Input.m_AimDirection = GameNetLUT::Atan2(player_obj->m_Velocity.y, player_obj->m_Velocity.x);

    if(ai_info.m_State == PlayerAIState::kSearchForNPCs)
    {
      if(ai_info.m_TargetPosition.IsValid() == false)
      {
        auto potential_points = stage.QueryNPCSpawns(player_obj->m_Position, 200, 1000);
        if(!potential_points.empty())
        {
          auto target_pos = potential_points[game.GetInstanceData().m_Random.GetRandom() % potential_points.size()];
          ai_info.m_TargetPosition = AITargetPos{target_pos.x, target_pos.y};
        }
      }

      auto targets = targeting.QueryForTargets(player_obj, GameNetVal(4), 200,
              GetDirectionForFacing(player_obj->m_Facing), 0xFFFFFFFF, &collision, game);


      for(auto & target : targets)
      {
        auto target_obj = target.ResolveTo<PlayerServerEntity>(game.GetObjectManager());
        if(target_obj)
        {
          ai_info.m_LastSeenPlayer = target_obj->GetSlotIndex();
          ai_info.m_State = PlayerAIState::kSearchForCover;
          ai_info.m_TargetPosition.Clear();
          ai_info.m_TimeInLos = 0;
          ai_info.m_TimeOutOfLos = 0;
          ai_info.m_CoverCounter = 0;
        }
      }
    }

    if(ai_info.m_State == PlayerAIState::kSearchForCover)
    {
      auto target_player = game.GetObjectManager().GetReservedSlotEntityAs<PlayerServerEntity>(ai_info.m_LastSeenPlayer);
      if(target_player == nullptr)
      {
        ai_info.m_State = PlayerAIState::kSearchForNPCs;
        return;
      }

      auto offset = target_player->m_Position - player_obj->m_Position;
      player_obj->m_Input.m_AimDirection = GameNetLUT::Atan2(offset.y, offset.x);

      if(ai_info.m_TargetPosition.IsValid() == false)
      {
        auto potential_points = stage.QueryNPCSpawns(player_obj->m_Position, 10, 250);
        for(auto & point : potential_points)
        {
          if(collision.CheckLineOfSight(target_player->m_Position, point, 0xFFFFFFFF))
          {
            ai_info.m_TargetPosition = AITargetPos{point.x, point.y};
            break;
          }
        }
      }

      if(collision.CheckLineOfSight(player_obj->m_Position, target_player->m_Position, 0xFFFFFFFF) == 0)
      {
        ai_info.m_TimeInLos++;
        ai_info.m_TimeOutOfLos = 0;
        if(ai_info.m_TimeInLos > 15)
        {
          player_obj->Fire(game);
          ai_info.m_TimeInLos = 0;
        }
      }
      else
      {
        ai_info.m_TimeInLos = 0;
        ai_info.m_TimeInLos++;

        if (ai_info.m_TimeOutOfLos > 250)
        {
          ai_info.m_State = PlayerAIState::kSearchForNPCs;
        }
      }
    }

    if(ai_info.m_TargetPosition)
    {
      auto target_pos = GameNetVec2(ai_info.m_TargetPosition->y, ai_info.m_TargetPosition->y);
      if(ManhattanDist(target_pos, player_obj->m_Position) < GameNetVal(4))
      {
        if(ai_info.m_State == PlayerAIState::kSearchForCover)
        {
          ai_info.m_CoverCounter++;
          if(ai_info.m_CoverCounter > 30)
          {
            ai_info.m_TargetPosition.Clear();
            ai_info.m_CoverCounter = 0;
          }
        }
        else
        {
          ai_info.m_TargetPosition.Clear();
        }
      }
      else
      {
        auto path = stage.FindPath(player_obj->m_Position, target_pos, 1000);
        if(path.size() > 0)
        {
          auto next_pos = path[0];

          if(ManhattanDist(target_pos, player_obj->m_Position) < GameNetVal(4) && path.size() > 1)
          {
            next_pos = path[1];
          }

          auto to_next = next_pos - player_obj->m_Position;
          player_obj->m_Input.m_InputAngle = GameNetLUT::Atan2(to_next.y, to_next.x);
          player_obj->m_Input.m_InputStr = GameNetVal(1);
        }
        else
        {
          ai_info.m_TargetPosition.Clear();
        }
      }
    }
  }
}
