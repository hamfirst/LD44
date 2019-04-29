#include "Game/GameCommon.h"

#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"

#include "GameShared/GameLogicContainer.h"

#include "Game/ServerObjects/Player/PlayerServerObject.refl.h"
#include "Game/ServerObjects/Bot/NPC/NPCBot.refl.meta.h"

#include "Project/Game/ServerObjects/Player/States/PlayerStateBite.refl.h"
#include "Project/Game/ServerObjects/Player/States/PlayerStateBite.refl.meta.h"

#include "Project/Game/ServerObjects/Player/States/PlayerStateIdle.refl.h"

#include "StormNet/NetReflectionTypeDatabase.h"

NET_REGISTER_TYPE(PlayerStateBite, PlayerStateBase);

CLIENT_ASSET(ClientAssetType::kVfx, "./VisualEffects/EatCharacter.vfx", g_EatVfx);
CLIENT_ASSET(ClientAssetType::kAudio, "./Sounds/BulletHitEnemy.wav", g_EatSfx);

void PlayerStateBite::Move(PlayerServerObject & player, GameLogicContainer & game_container)
{
  player.m_Velocity.x = 0;
  player.m_Velocity.y = 0;
}

void PlayerStateBite::Transition(PlayerServerObject & player, GameLogicContainer & game_container)
{
  if (m_Finished || player.m_Bat)
  {
    player.TransitionToState<PlayerStateIdle>(game_container);
  }
}

void PlayerStateBite::Animate(PlayerServerObject & player, GameLogicContainer & game_container)
{
  m_Finished = player.FrameAdvance(COMPILE_TIME_CRC32_STR("Bite"));
  if(player.m_AnimFrame == 1 && player.m_AnimDelay == 0)
  {
    game_container.GetEventSender().SendVfxEvent(player.m_Position - GameNetVec2(0, 5), g_EatVfx);
    game_container.GetEventSender().SendSoundEvent(player.m_Position, g_EatSfx, false);
  }

  player.TriggerAnimationEvents(game_container, *this);
}


void PlayerStateBite::Cleanup(PlayerServerObject & player, GameLogicContainer & game_container)
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