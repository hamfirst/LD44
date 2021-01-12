
#include "GameProject/GameCommon.h"

#include "GameProject/GameController.refl.h"
#include "GameProject/GameServerEventSender.h"

#include "GameProject/ServerEntities/Bot/BotBehaviorTree.h"
#include "GameProject/ServerEntities/Bot/TestBot/TestBot.refl.h"
#include "GameProject/ServerEntities/Bot/TestBot/TestBot.refl.meta.h"

#include "Runtime/ClientEntity/ClientEntityResource.h"

GLOBAL_ASSET(ClientEntityResourcePtr, "./Gameplay/TestBot.entity", g_TestBotEntity);

static StormBehaviorTreeTemplate<BotServerObject, GameServerWorld> BehaviorTreeTemplate =
  SELECT()
    .AddChild(
            STATE<PlayAnimationBotState>(COMPILE_TIME_CRC32_STR("Idle"))
            )
;

TestBot::TestBot()
{
  m_Tree.SetBehaviorTree(&BehaviorTreeTemplate);
}

void TestBot::Init(const TestBotInitData & init_data, GameServerWorld & game_world)
{

}

void TestBot::UpdateFirst(GameServerWorld & game_world)
{
  BotServerObject::UpdateFirst(game_container);
}

void TestBot::UpdateMiddle(GameServerWorld & game_world)
{
  BotServerObject::UpdateMiddle(game_container);
}

czstr TestBot::GetDefaultEntityBinding() const
{
  return "./Gameplay/TestBot.entity";
}

const SpritePtr & TestBot::GetSprite() const
{
  return g_TestBotEntity->GetSprite();
}

NullOptPtr<BotBehaviorTree> TestBot::GetBehaviorTree()
{
  return &m_Tree;
}
