#pragma once

#include "Game/GameCommon.h"

#include "GameShared/GameLogicContainer.h"
#include "GameShared/Systems/GameLogicSystems.h"

#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"
#include "Game/ServerObjects/Bot/BotServerObject.refl.h"

#include "Runtime/ServerObject/ServerObject.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.h"
#include "Runtime/ServerObject/ServerObjectRegistrationMacros.h"
#include "Runtime/Map/MapHandles.refl.h"

struct NPCBotInitData : public BotServerObjectInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(NPCBotInitData);
  RInt m_NPCIndex;
};

class NPCBot : public BotServerObject
{
public:
  DECLARE_SERVER_OBJECT;

  NPCBot();
  NPCBot(const NPCBot & rhs) = default;
  NPCBot(NPCBot && rhs) = default;

  NPCBot & operator = (const NPCBot & rhs) = default;
  NPCBot & operator = (NPCBot && rhs) = default;

  void Init(const NPCBotInitData & init_data, GameLogicContainer & game_container);
  void UpdateFirst(GameLogicContainer & game_container);
  void UpdateMiddle(GameLogicContainer & game_container);
  void UpdateLast(GameLogicContainer & game_container);

  bool SERVER_OBJECT_EVENT_HANDLER HandleDamageEvent(const DamageEvent & ev, const EventMetaData & meta);

  virtual czstr GetDefaultEntityBinding() const override;
  virtual czstr GetEntityBinding() const override;

  virtual const SpritePtr & GetSprite() const override;

  virtual NullOptPtr<BotBehaviorTree> GetBehaviorTree() override;
public:

  BotBehaviorTree m_Tree;

  int8_t m_NPCIndex = 0;
};
