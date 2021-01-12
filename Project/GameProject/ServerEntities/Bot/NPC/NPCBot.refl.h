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

  void Init(const NPCBotInitData & init_data, GameServerWorld & game_world);
  void UpdateFirst(GameServerWorld & game_world);
  void UpdateMiddle(GameServerWorld & game_world);
  void UpdateLast(GameServerWorld & game_world);

  bool SERVER_ENTITY_EVENT_HANDLER HandleDamageEvent(const DamageEvent & ev, const EventMetaData & meta);

  virtual czstr GetDefaultEntityBinding() const override;
  virtual czstr GetEntityBinding() const override;

  virtual const SpritePtr & GetSprite() const override;

  virtual NullOptPtr<BotBehaviorTree> GetBehaviorTree() override;
public:

  BotBehaviorTree m_Tree;

  int8_t m_NPCIndex = 0;
};
