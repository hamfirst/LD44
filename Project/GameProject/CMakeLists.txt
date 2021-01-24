cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}
                    ${PROJECT_SOURCE_DIR}/External
                    ${PROJECT_SOURCE_DIR}/StormTech
                    ${PROJECT_SOURCE_DIR}/Tools
                    ${PROJECT_SOURCE_DIR}/Shared
                    ${PROJECT_SOURCE_DIR}/Project
                    ${PROJECT_SOURCE_DIR}/Lobby)

set(CMAKE_CXX_STANDARD 17)

include("${PROJECT_SOURCE_DIR}/CMake/cotire.cmake")

set(GENERIC_SRC_GameProject 
            AI/PlayerAI.cpp
            Data/CoverPoint.refl.reg.cpp
            Data/DealDamageAnimationEvent.refl.reg.cpp
            Data/KillVolume.refl.reg.cpp
            Data/NPCSpawn.refl.reg.cpp
            Data/PlayerSpawn.refl.reg.cpp
            GameCommon.cpp
            GameConfig.refl.reg.cpp
            GameController.refl.cpp
            GameMessages.refl.cpp
            GameNetworkEvents.refl.cpp
            GameNetworkExternals.refl.cpp
            GameServerEventSender.cpp
            GameServerTypes.cpp
            GameStage.cpp
            ServerEntities/Bot/BotServerObject.refl.cpp
            ServerEntities/Bot/BotServerObject.refl.reg.cpp
            ServerEntities/Bot/NPC/NPCBot.refl.cpp
            ServerEntities/Bot/NPC/NPCBot.refl.reg.cpp
            ServerEntities/Bot/TestBot/TestBot.refl.cpp
            ServerEntities/Bot/TestBot/TestBot.refl.reg.cpp
            ServerEntities/CharacterFacing.refl.cpp
            ServerEntities/GameServerEntityBase.refl.cpp
            ServerEntities/GameServerEntityBase.refl.reg.cpp
            ServerEntities/Pickups/HealthPickup/HealthPickup.refl.cpp
            ServerEntities/Pickups/HealthPickup/HealthPickup.refl.reg.cpp
            ServerEntities/Pickups/PickupBase.refl.cpp
            ServerEntities/Pickups/PickupBase.refl.reg.cpp
            ServerEntities/Player/PlayerConfig.refl.reg.cpp
            ServerEntities/Player/PlayerServerEntity.refl.cpp
            ServerEntities/Player/PlayerServerEntity.refl.reg.cpp
            ServerEntities/Player/States/PlayerStateBase.refl.cpp
            ServerEntities/Player/States/PlayerStateBasicAttack.refl.cpp
            ServerEntities/Player/States/PlayerStateBite.refl.cpp
            ServerEntities/Player/States/PlayerStateIdle.refl.cpp
            ServerEntities/Player/States/PlayerStateJump.refl.cpp
            ServerEntities/Player/States/PlayerStateMoving.refl.cpp
            ServerEntities/Projectile/Motion/ProjectileMotionBase.refl.cpp
            ServerEntities/Projectile/Motion/ProjectileMotionLinear.refl.cpp
            ServerEntities/Projectile/ProjectileConfig.refl.reg.cpp
            ServerEntities/Projectile/ProjectileServerEntity.refl.cpp
            ServerEntities/Projectile/ProjectileServerEntity.refl.reg.cpp
            ServerEntities/Projectile/Response/ProjectileResponseBase.refl.cpp
            ServerEntities/Projectile/Response/ProjectileResponseDefault.refl.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_GameProject 
            AI/PlayerAI.h
            Data/CoverPoint.refl.h
            Data/DealDamageAnimationEvent.refl.h
            Data/KillVolume.refl.h
            Data/NPCSpawn.refl.h
            Data/PlayerSpawn.refl.h
            GameCollisionType.refl.h
            GameCommon.h
            GameConfig.refl.h
            GameController.refl.h
            GameMessages.refl.h
            GameNetworkData.refl.h
            GameNetworkEvents.refl.h
            GameNetworkExternals.refl.h
            GameServerEventSender.h
            GameServerTypes.h
            GameSimulationEventCallbacks.h
            GameSimulationStats.refl.h
            GameStage.h
            GameplayEvents/DamageEvent.h
            GameplayEvents/DamageType.refl.h
            GameplayEvents/PickupEvents.h
            GameplayEvents/PlaceholderEvent.h
            ServerEntities/Bot/BotBehaviorTree.h
            ServerEntities/Bot/BotServerObject.refl.h
            ServerEntities/Bot/NPC/NPCBot.refl.h
            ServerEntities/Bot/TestBot/TestBot.refl.h
            ServerEntities/CharacterFacing.refl.h
            ServerEntities/GameServerEntityBase.refl.h
            ServerEntities/Pickups/HealthPickup/HealthPickup.refl.h
            ServerEntities/Pickups/PickupBase.refl.h
            ServerEntities/Player/PlayerConfig.refl.h
            ServerEntities/Player/PlayerServerEntity.refl.h
            ServerEntities/Player/States/PlayerStateBase.refl.h
            ServerEntities/Player/States/PlayerStateBasicAttack.refl.h
            ServerEntities/Player/States/PlayerStateBite.refl.h
            ServerEntities/Player/States/PlayerStateIdle.refl.h
            ServerEntities/Player/States/PlayerStateJump.refl.h
            ServerEntities/Player/States/PlayerStateMoving.refl.h
            ServerEntities/Projectile/Motion/ProjectileMotionBase.refl.h
            ServerEntities/Projectile/Motion/ProjectileMotionLinear.refl.h
            ServerEntities/Projectile/ProjectileConfig.refl.h
            ServerEntities/Projectile/ProjectileServerEntity.refl.h
            ServerEntities/Projectile/Response/ProjectileResponseBase.refl.h
            ServerEntities/Projectile/Response/ProjectileResponseDefault.refl.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_GameProject 
            Data/CoverPoint.refl.h
            Data/DealDamageAnimationEvent.refl.h
            Data/KillVolume.refl.h
            Data/NPCSpawn.refl.h
            Data/PlayerSpawn.refl.h
            GameCollisionType.refl.h
            GameConfig.refl.h
            GameController.refl.h
            GameMessages.refl.h
            GameNetworkData.refl.h
            GameNetworkEvents.refl.h
            GameNetworkExternals.refl.h
            GameSimulationStats.refl.h
            GameplayEvents/DamageType.refl.h
            ServerEntities/Bot/BotServerObject.refl.h
            ServerEntities/Bot/NPC/NPCBot.refl.h
            ServerEntities/Bot/TestBot/TestBot.refl.h
            ServerEntities/CharacterFacing.refl.h
            ServerEntities/GameServerEntityBase.refl.h
            ServerEntities/Pickups/HealthPickup/HealthPickup.refl.h
            ServerEntities/Pickups/PickupBase.refl.h
            ServerEntities/Player/PlayerConfig.refl.h
            ServerEntities/Player/PlayerServerEntity.refl.h
            ServerEntities/Player/States/PlayerStateBase.refl.h
            ServerEntities/Player/States/PlayerStateBasicAttack.refl.h
            ServerEntities/Player/States/PlayerStateBite.refl.h
            ServerEntities/Player/States/PlayerStateIdle.refl.h
            ServerEntities/Player/States/PlayerStateJump.refl.h
            ServerEntities/Player/States/PlayerStateMoving.refl.h
            ServerEntities/Projectile/Motion/ProjectileMotionBase.refl.h
            ServerEntities/Projectile/Motion/ProjectileMotionLinear.refl.h
            ServerEntities/Projectile/ProjectileConfig.refl.h
            ServerEntities/Projectile/ProjectileServerEntity.refl.h
            ServerEntities/Projectile/Response/ProjectileResponseBase.refl.h
            ServerEntities/Projectile/Response/ProjectileResponseDefault.refl.h
            #REFL_PLACEHOLDER
            )

if(GENERATE_REFL)
  foreach(REFL_FILE ${GENERIC_REFL_GameProject})
    string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
    add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                       COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/StormTech -I${PROJECT_SOURCE_DIR}/Tools -I${PROJECT_SOURCE_DIR}/Shared -I${PROJECT_SOURCE_DIR}/Project -I${PROJECT_SOURCE_DIR}/Lobby -I${PROJECT_SOURCE_DIR}/External ${CLANG_COMMAND_LINE_OPTS} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                       MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                       IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
  endforeach()
endif()

add_library(GameProject STATIC ${GENERIC_SRC_GameProject} ${GENERIC_HEADER_GameProject})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_GameProject} ${GENERIC_HEADER_GameProject})

set_target_properties(GameProject PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT GameCommon.h)

if(GENERATE_PCH)
  cotire(GameProject)
endif()
