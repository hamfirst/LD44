
#include "GameProject/GameCommon.h"

#include "GameProject/GameController.refl.h"
#include "GameProject/GameServerEventSender.h"

#include "GameProject/ServerEntities/Bot/BotBehaviorTree.h"

#include "GameProject/ServerEntities/Bot/NPC/NPCBot.refl.h"
#include "GameProject/ServerEntities/Bot/NPC/NPCBot.refl.meta.h"

#include "Runtime/ClientEntity/ClientEntityResource.h"
#include "Runtime/Sprite/SpriteResource.h"

GLOBAL_ASSET(ClientEntityResourcePtr, "./Gameplay/NPC1.entity", g_NPC1Entity);
GLOBAL_ASSET(ClientEntityResourcePtr, "./Gameplay/NPC2.entity", g_NPC2Entity);
GLOBAL_ASSET(ClientEntityResourcePtr, "./Gameplay/NPC3.entity", g_NPC3Entity);
GLOBAL_ASSET(ClientEntityResourcePtr, "./Gameplay/NPC4.entity", g_NPC4Entity);

GLOBAL_ASSET(SpritePtr, "./Gameplay/Alert.sprite", g_AlertSprite);

CLIENT_ASSET(ClientAssetType::kAudio, "./Sounds/GuyScream.wav", g_NPC1Alert);
CLIENT_ASSET(ClientAssetType::kAudio, "./Sounds/GuyScream2.wav", g_NPC2Alert);
CLIENT_ASSET(ClientAssetType::kAudio, "./Sounds/GirlScream.wav", g_NPC3Alert);
CLIENT_ASSET(ClientAssetType::kAudio, "./Sounds/PigSqueal.wav", g_NPC4Alert);

static StormBehaviorTreeTemplate<BotServerObject, GameServerWorld> BehaviorTreeTemplate =

        SELECT()
        .AddChild(
                STATE<PlayAnimationBotState>(COMPILE_TIME_CRC32_STR("Idle"))
                        .AddConditional<IsBeingEatenBotConditional>(true, false)
        )
        .AddChild(
                STATE<PlayAnimationBotState>(COMPILE_TIME_CRC32_STR("Dead"))
                        .AddConditional<IsDeadBotConditional>(true, false)
        )
        .AddChild(
                STATE<PlayAnimationBotState>(COMPILE_TIME_CRC32_STR("Idle"))
                        .AddConditional<IsAlertedBotConditional>(true, false)
        )
        .AddChild(
                SEQUENCE()
                .AddChild(
                        STATE<PlayAnimationForTimeBotState>(COMPILE_TIME_CRC32_STR("Idle"), 240)
                )
                .AddChild(
                        STATE<MoveForTimeBotState>(GameNetVec2(1, 0), COMPILE_TIME_CRC32_STR("Move"), 40, true)
                )
                .AddChild(
                        STATE<PlayAnimationForTimeBotState>(COMPILE_TIME_CRC32_STR("Idle"), 240)
                )
                .AddChild(
                        STATE<MoveForTimeBotState>(GameNetVec2(-1, 0), COMPILE_TIME_CRC32_STR("Move"), 40, true)
                )
        )
;

NPCBot::NPCBot()
{
  m_Tree.SetBehaviorTree(&BehaviorTreeTemplate);
}

void NPCBot::Init(const NPCBotInitData & init_data, GameServerWorld & game_world)
{
  m_NPCIndex = init_data.m_NPCIndex;
}

void NPCBot::UpdateFirst(GameServerWorld & game_world)
{
  BotServerObject::UpdateFirst(game_container);
}

void NPCBot::UpdateMiddle(GameServerWorld & game_world)
{
  BotServerObject::UpdateMiddle(game_container);

  if(!m_Dead && !m_BeingEaten)
  {
    PushReceiveDamageEventBoxes(COMPILE_TIME_CRC32_STR("ReceiveDamage"), game_container);
    PushReceiveDamageCollisionBoxes(COMPILE_TIME_CRC32_STR("ReceiveDamage"), game_container);
  }
}

void NPCBot::UpdateLast(GameServerWorld & game_world)
{
  if(m_AlertedFrames > 0)
  {
    --m_AlertedFrames;
  }


  if(!m_Dead && !m_BeingEaten && m_AlertedFrames == 0)
  {
    auto facing = GetDirectionForFacing(m_Facing);
    auto targets = QueryTargetDatabase(GameNetVal("1.5"), GameNetVal(130), facing, 0xFFFFFFFF, game_container);
    if(!targets.empty())
    {
      m_AlertedFrames = 200;

      game_container.GetEventSender().SendVfxSpriteEvent(m_Position, g_AlertSprite, COMPILE_TIME_CRC32_STR("Alert"));


      uint32_t sound_hash = 0;
      switch(m_NPCIndex)
      {
        default:
        case 0:
          sound_hash = g_NPC1Alert;
          break;
        case 1:
          sound_hash = g_NPC2Alert;
          break;
        case 2:
          sound_hash = g_NPC3Alert;
          break;
        case 3:
          sound_hash = g_NPC4Alert;
          break;
      }

      game_container.GetEventSender().SendSoundEvent(m_Position, sound_hash, true);
    }
  }

}

bool NPCBot::HandleDamageEvent(const DamageEvent & ev, const EventMetaData & meta)
{
  m_Dead = true;
  return true;
}

czstr NPCBot::GetDefaultEntityBinding() const
{
  return "./Gameplay/NPC1.entity";
}

czstr NPCBot::GetEntityBinding() const
{
  switch(m_NPCIndex)
  {
    default:
    case 0:
      return g_NPC1Entity->GetFileName();
    case 1:
      return g_NPC2Entity->GetFileName();
    case 2:
      return g_NPC3Entity->GetFileName();
    case 3:
      return g_NPC4Entity->GetFileName();
  }
}

const SpritePtr & NPCBot::GetSprite() const
{
  switch(m_NPCIndex)
  {
    default:
    case 0:
      return g_NPC1Entity->GetSprite();
    case 1:
      return g_NPC2Entity->GetSprite();
    case 2:
      return g_NPC3Entity->GetSprite();
    case 3:
      return g_NPC4Entity->GetSprite();
  }
}

NullOptPtr<BotBehaviorTree> NPCBot::GetBehaviorTree()
{
  return &m_Tree;
}
