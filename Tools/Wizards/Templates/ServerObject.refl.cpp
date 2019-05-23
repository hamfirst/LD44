
#include ""Game/GameCommon.h""

#include ""Game/GameController.refl.h""
#include ""Game/GameServerEventSender.h""

#include ""Runtime/Entity/EntityResource.h""

#include ""{rel_path}/{refl_header_file}""
#include ""{rel_path}/{refl_meta_file}""

czstr g_{class_name}EntityFile = "./Gameplay/ClientEntity.entity";
GLOBAL_ASSET(EntityResourcePtr, g_{class_name}EntityFile, g_{class_name}Entity);

void {class_name}::Init(const {class_name}InitData & init_data, GameLogicContainer & game_container)
{{

}}

void {class_name}::UpdateFirst(GameLogicContainer & game_container)
{{

}}

void {class_name}::UpdateMiddle(GameLogicContainer & game_container)
{{

}}

czstr {class_name}::GetDefaultEntityBinding() const
{{
  return g_{class_name}EntityFile;
}}

const SpritePtr & {class_name}::GetSprite() const
{{
  return g_{class_name}Entity->GetSprite();
}}
