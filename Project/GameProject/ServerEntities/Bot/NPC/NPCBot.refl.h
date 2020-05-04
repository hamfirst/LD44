#pragma once

#include "Game/GameCommon.h"

#include "GameShared/GameServerWorld.h"
#include "GameShared/Systems/GameLogicSystems.h"

#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"
#include "Game/ServerEntities/Bot/BotServerObject.refl.h"

#include "Runtime/ServerEntity/ServerEntity.h"
#include "Runtime/ServerEntity/ServerEntityInitData.refl.h"
#include "Runtime/ServerEntity/ServerEntityRegistrationMacros.h"
#include "Runtime/Map/MapHandles.refl.h"

struct NPCBotInitData : public BotServerObjectInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(NPCBotInitData);
  RInt m_NPCIndex;
};

class NPCBot : public BotServerObject
{
public:
  DECLARE_SERVER_ENTITY;

  NPCBot();
  NPCBot(const NPCBot & rhs) = default;
  NPCBot(NPCBot && rhs) = default;

  NPCBot & operator = (const NPCBot & rhs) = default;
  NPCBot & operator = (NPCBot && rhs) = default;

  void Init(const NPCBotInitData & init_data, GameServerWorld & game_container);
  void UpdateFirst(GameServerWorld & game_container);
  void UpdateMiddle(GameServerWorld & game_container);
  void UpdateLast(GameServerWorld & game_container);

  bool SERVER_ENTITY_EVENT_HANDLER HandleDamageEvent(const DamageEvent & ev, const EventMetaData & meta);

  virtual czstr GetDefaultEntityBinding() const override;
  virtual czstr GetEntityBinding() const override;

  virtual const SpritePtr & GetSprite() const override;

  virtual NullOptPtr<BotBehaviorTree> GetBehaviorTree() override;
public:

  BotBehaviorTree m_Tree;

  int8_t m_NPCIndex = 0;
};
