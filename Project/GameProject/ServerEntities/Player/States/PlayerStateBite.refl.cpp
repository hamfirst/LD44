#include "GameProject/GameCommon.h"

#include "GameProject/GameServerEventSender.h"
#include "GameProject/GameStage.h"

#include "Project/GameServerFramework/GameServerWorld.h"

#include "GameProject/ServerEntities/Player/PlayerServerEntity.refl.h"
#include "GameProject/ServerEntities/Bot/NPC/NPCBot.refl.meta.h"

#include "GameProject/ServerEntities/Player/States/PlayerStateBite.refl.h"
#include "GameProject/ServerEntities/Player/States/PlayerStateBite.refl.meta.h"

#include "GameProject/ServerEntities/Player/States/PlayerStateIdle.refl.h"

#include "StormNet/NetReflectionTypeDatabase.h"

NET_REGISTER_TYPE(PlayerStateBite, PlayerStateBase);

CLIENT_ASSET(ClientAssetType::kVfx, "./VisualEffects/EatCharacter.vfx", g_EatVfx);
CLIENT_ASSET(ClientAssetType::kAudio, "./Sounds/BulletHitEnemy.wav", g_EatSfx);

void PlayerStateBite::Move(PlayerServerEntity & player, GameServerWorld & game_world)
{
  player.m_Velocity.x = 0;
  player.m_Velocity.y = 0;
}

void PlayerStateBite::Transition(PlayerServerEntity & player, GameServerWorld & game_world)
{
  if (m_Finished || player.m_Bat)
  {
    player.TransitionToState<PlayerStateIdle>(game_container);
  }
}

void PlayerStateBite::Animate(PlayerServerEntity & player, GameServerWorld & game_world)
{
  m_Finished = player.FrameAdvance(COMPILE_TIME_CRC32_STR("Bite"));
  if(player.m_AnimFrame == 1 && player.m_AnimDelay == 0)
  {
    game_container.GetEventSender().SendVfxEvent(player.m_Position - GameNetVec2(0, 5), g_EatVfx);
    game_container.GetEventSender().SendSoundEvent(player.m_Position, g_EatSfx, false);
  }

  player.TriggerAnimationEvents(game_container, *this);
}


void PlayerStateBite::Cleanup(PlayerServerEntity & player, GameServerWorld & game_world)
{
  if(m_Finished)
  {
    player.GiveHealth(2);

    auto npc = player.m_NPCBeingEaten.ResolveTo<NPCBot>(game_container.GetObjectManager());
    if(npc)
    {
      npc->Destroy(game_container.GetObjectManager());
    }
  }
  else
  {
    auto npc = player.m_NPCBeingEaten.ResolveTo<NPCBot>(game_container.GetObjectManager());
    if(npc)
    {
      npc->m_BeingEaten = false;
      npc->m_Dead = true;
    }
  }

  player.m_NPCBeingEaten.Reset();
}