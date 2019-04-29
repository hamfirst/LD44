#include ""Game/GameCommon.h""

#include ""Game/GameServerEventSender.h""
#include ""Game/GameStage.h""

#include ""GameShared/GameLogicContainer.h""

#include ""{rel_path}/{refl_header_file}""
#include ""{rel_path}/{refl_meta_file}""

{class_name}::{class_name}()
{{

}}

void {class_name}::Activate(BotServerObject & bot, GameLogicContainer & container)
{{
  bot.ResetAnimState();
}}

bool {class_name}::Update(BotServerObject & bot, GameLogicContainer & container)
{{
  return true;
}}
