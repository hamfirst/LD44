#pragma once

#include "Game/GameCommon.h"

#include "GameShared/GameLogicContainer.h"
#include "GameShared/Systems/GameLogicSystems.h"

#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"
#include "Game/ServerEntities/Bot/BotServerObject.refl.h"

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

  void Init(const TestBotInitData & init_data, GameLogicContainer & game_container);
  void UpdateFirst(GameLogicContainer & game_container);
  void UpdateMiddle(GameLogicContainer & game_container);

  virtual czstr GetDefaultEntityBinding() const override;
  virtual const SpritePtr & GetSprite() const override;

  virtual NullOptPtr<BotBehaviorTree> GetBehaviorTree() override;
public:

  BotBehaviorTree m_Tree;

};
