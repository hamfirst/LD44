
#include ""Game/GameCommon.h""

#include ""Game/GameController.refl.h""
#include ""Game/GameServerEventSender.h""

#include ""Game/ServerObjects/Bot/BotBehaviorTree.h""

#include ""{rel_path}/{refl_header_file}""
#include ""{rel_path}/{refl_meta_file}""

#include ""Runtime/Entity/EntityResource.h""

GLOBAL_ASSET(EntityResourcePtr, ""./Gameplay/{class_name}.entity"", g_{class_name}Entity);

static StormBehaviorTreeTemplate<BotServerObject, GameLogicContainer> BehaviorTreeTemplate =
  SELECT()
    .AddChild(
            STATE<PlayAnimationBotState>(COMPILE_TIME_CRC32_STR(""Idle""))
            )
;

{class_name}::{class_name}()
{{
  m_Tree.SetBehaviorTree(&BehaviorTreeTemplate);
}}

void {class_name}::Init(const {class_name}InitData & init_data, GameLogicContainer & game_container)
{{

}}

void {class_name}::UpdateFirst(GameLogicContainer & game_container)
{{
  BotServerObject::UpdateFirst(game_container);
}}

void {class_name}::UpdateMiddle(GameLogicContainer & game_container)
{{
  BotServerObject::UpdateMiddle(game_container);
}}

czstr {class_name}::GetDefaultEntityBinding() const
{{
  return ""./Gameplay/{class_name}.entity"";
}}

const SpritePtr & {class_name}::GetSprite() const
{{
  return g_{class_name}Entity->GetSprite();
}}

NullOptPtr<BotBehaviorTree> {class_name}::GetBehaviorTree()
{{
  return &m_Tree;
}}
