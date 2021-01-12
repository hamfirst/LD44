#pragma once

#include "GameProject/GameCommon.h"

#include "Project/GameServerFramework/GameServerWorld.h"

#include "GameProject/GameServerEventSender.h"
#include "GameProject/GameStage.h"
#include "GameProject/ServerEntities/Bot/BotServerObject.refl.h"

#include "Runtime/ServerEntity/ServerEntity.h"
#include "Runtime/ServerEntity/ServerEntityInitData.refl.h"
#include "Runtime/ServerEntity/ServerEntityRegistrationMacros.h"
#include "Runtime/Map/MapHandles.refl.h"

struct TestBotInitData : public BotServerObjectInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(TestBotInitData);
};

class TestBot : public BotServerObject
{
public:
  DECLARE_SERVER_ENTITY;

  TestBot();
  TestBot(const TestBot & rhs) = default;
  TestBot(TestBot && rhs) = default;

  TestBot & operator = (const TestBot & rhs) = default;
  TestBot & operator = (TestBot && rhs) = default;

  void Init(const TestBotInitData & init_data, GameServerWorld & game_world);
  void UpdateFirst(GameServerWorld & game_world);
  void UpdateMiddle(GameServerWorld & game_world);

  virtual czstr GetDefaultEntityBinding() const override;
  virtual const SpritePtr & GetSprite() const override;

  virtual NullOptPtr<BotBehaviorTree> GetBehaviorTree() override;
public:

  BotBehaviorTree m_Tree;

};
