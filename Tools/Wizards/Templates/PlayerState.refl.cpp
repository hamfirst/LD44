#include ""Game/GameCommon.h""
#include ""Game/GameServerEventSender.h""
#include ""Game/GameStage.h""

#include ""GameShared/GameLogicContainer.h""

#include ""Game/ServerObjects/Player/PlayerServerEntity.refl.h""

#include ""{rel_path}/{refl_header_file}""
#include ""{rel_path}/{refl_meta_file}""

#include ""StormNet/NetReflectionTypeDatabase.h""

NET_REGISTER_TYPE({class_name}, PlayerStateBase);

void {class_name}::Move(PlayerServerEntity & player, GameLogicContainer & game_container)
{{

}}

void {class_name}::Transition(PlayerServerEntity & player, GameLogicContainer & game_container)
{{

}}

void {class_name}::Animate(PlayerServerEntity & player, GameLogicContainer & game_container)
{{
  player.FrameAdvance(COMPILE_TIME_CRC32_STR(""Animation""));
  player.TriggerAnimationEvents(game_container, *this);
}}
