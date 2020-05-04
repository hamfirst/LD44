#include "Game/GameCommon.h"

#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"

#include "GameShared/GameServerWorld.h"

#include "Game/ServerEntities/Player/PlayerServerEntity.refl.h"
#include "Game/ServerEntities/Bot/NPC/NPCBot.refl.meta.h"

#include "Game/ServerEntities/Player/States/PlayerStateBite.refl.h"
#include "Game/ServerEntities/Player/States/PlayerStateBite.refl.meta.h"

#include "Game/ServerEntities/Player/States/PlayerStateIdle.refl.h"

#include "StormNet/NetReflectionTypeDatabase.h"

NET_REGISTER_TYPE(PlayerStateBite, PlayerStateBase);

CLIENT_ASSET(ClientAssetType::kVfx, "./VisualEffects/EatCharacter.vfx", g_EatVfx);
CLIENT_ASSET(ClientAssetType::kAudio, "./Sounds/BulletHitEnemy.wav", g_EatSfx);

void PlayerStateBite::Move(PlayerServerEntity & player, GameServerWorld & game_container)
{
  player.m_Velocity.x = 0;
  player.m_Velocity.y = 0;
}

void PlayerStateBite::Transition(PlayerServerEntity & player, GameServerWorld & game_container)
{
  if (m_Finished || player.m_Bat)
  {
    player.TransitionToState<PlayerStateIdle>(game_container);
  }
}

void PlayerStateBite::Animate(PlayerServerEntity & player, GameServerWorld & game_container)
{
  m_Finished = player.FrameAdvance(COMPILE_TIME_CRC32_STR("Bite"));
  if(player.m_AnimFrame == 1 && player.m_AnimDelay == 0)
  {
    game_container.GetEventSender().SendVfxEvent(player.m_Position - GameNetVec2(0, 5), g_EatVfx);
    game_container.GetEventSender().SendSoundEvent(player.m_Position, g_EatSfx, false);
  }

  player.TriggerAnimationEvents(game_container, *this);
}


void PlayerStateBite::Cleanup(PlayerServerEntity & player, GameServerWorld & game_container)
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