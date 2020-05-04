#pragma once

#include ""Game/GameCommon.h""

#include ""GameShared/GameServerWorld.h""
#include ""GameShared/Systems/GameLogicSystems.h""

#include ""Game/GameServerEventSender.h""
#include ""Game/GameStage.h""
#include ""Game/ServerObjects/Bot/BotServerObject.refl.h""

#include ""Runtime/ServerObject/ServerObject.h""
#include ""Runtime/ServerObject/ServerObjectInitData.refl.h""
#include ""Runtime/ServerObject/ServerObjectRegistrationMacros.h""
#include ""Runtime/Map/MapHandles.refl.h""

struct {class_name}InitData : public BotServerObjectInitData
{{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED({class_name}InitData);
}};

class {class_name} : public BotServerObject
{{
public:
  DECLARE_SERVER_OBJECT;

  {class_name}();
  {class_name}(const {class_name} & rhs) = default;
  {class_name}({class_name} && rhs) = default;

  {class_name} & operator = (const {class_name} & rhs) = default;
  {class_name} & operator = ({class_name} && rhs) = default;

  void Init(const {class_name}InitData & init_data, GameLogicContainer & game_container);
  void UpdateFirst(GameLogicContainer & game_container);
  void UpdateMiddle(GameLogicContainer & game_container);

  virtual czstr GetDefaultEntityBinding() const override;
  virtual const SpritePtr & GetSprite() const override;

  virtual NullOptPtr<BotBehaviorTree> GetBehaviorTree() override;
public:

  BotBehaviorTree m_Tree;

}};
