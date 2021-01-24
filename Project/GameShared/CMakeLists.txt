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

set(GENERIC_SRC_GameShared 
            BehaviorTree/BehaviorTreeTypeDatabase.cpp
            BehaviorTree/Conditionals/IsAlertedBotConditional.refl.cpp
            BehaviorTree/Conditionals/IsAlertedBotConditional.refl.reg.cpp
            BehaviorTree/Conditionals/IsBeingEatenBotConditional.refl.cpp
            BehaviorTree/Conditionals/IsBeingEatenBotConditional.refl.reg.cpp
            BehaviorTree/Conditionals/IsDeadBotConditional.refl.cpp
            BehaviorTree/Conditionals/IsDeadBotConditional.refl.reg.cpp
            BehaviorTree/States/MoveForTimeBotState.refl.cpp
            BehaviorTree/States/MoveForTimeBotState.refl.reg.cpp
            BehaviorTree/States/PlayAnimationBotState.refl.cpp
            BehaviorTree/States/PlayAnimationBotState.refl.reg.cpp
            BehaviorTree/States/PlayAnimationForTimeBotState.refl.cpp
            BehaviorTree/States/PlayAnimationForTimeBotState.refl.reg.cpp
            GameSharedCommon.cpp
            Level/GameLevelList.cpp
            Level/GameStageManager.cpp
            Modifier/Modifier.refl.cpp
            Modifier/Modifier.refl.reg.cpp
            PlayList/GamePlayList.cpp
            SkillTree/SkillTree.cpp
            SkillTree/SkillTreeCompiled.cpp
            SkillTree/SkillTreeConfig.refl.reg.cpp
            Systems/CVCPushSystem.cpp
            Systems/GameServerEntityOverlapSystem.cpp
            Systems/TargetDatabase.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_GameShared 
            BehaviorTree/BehaviorTree.h
            BehaviorTree/BehaviorTreeSerialize.h
            BehaviorTree/BehaviorTreeTypeDatabase.h
            BehaviorTree/Conditionals/IsAlertedBotConditional.refl.h
            BehaviorTree/Conditionals/IsBeingEatenBotConditional.refl.h
            BehaviorTree/Conditionals/IsDeadBotConditional.refl.h
            BehaviorTree/States/MoveForTimeBotState.refl.h
            BehaviorTree/States/PlayAnimationBotState.refl.h
            BehaviorTree/States/PlayAnimationForTimeBotState.refl.h
            GameProtocol.h
            GameSharedCommon.h
            Level/GameLevelList.h
            Level/GameLevelListAsset.refl.h
            Level/GameStageManager.h
            Modifier/Modifier.refl.h
            PlayList/GamePlayList.h
            PlayList/GamePlayListAsset.refl.h
            SkillTree/SkillTree.h
            SkillTree/SkillTreeCompiled.h
            SkillTree/SkillTreeConfig.refl.h
            SkillTree/SkillTreeSerialize.h
            Systems/CVCPushSystem.h
            Systems/GameServerEntityOverlapRegistrationMacros.h
            Systems/GameServerEntityOverlapSystem.h
            Systems/TargetDatabase.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_GameShared 
            BehaviorTree/Conditionals/IsAlertedBotConditional.refl.h
            BehaviorTree/Conditionals/IsBeingEatenBotConditional.refl.h
            BehaviorTree/Conditionals/IsDeadBotConditional.refl.h
            BehaviorTree/States/MoveForTimeBotState.refl.h
            BehaviorTree/States/PlayAnimationBotState.refl.h
            BehaviorTree/States/PlayAnimationForTimeBotState.refl.h
            Level/GameLevelListAsset.refl.h
            Modifier/Modifier.refl.h
            PlayList/GamePlayListAsset.refl.h
            SkillTree/SkillTreeConfig.refl.h
            #REFL_PLACEHOLDER
            )

if(GENERATE_REFL)
  foreach(REFL_FILE ${GENERIC_REFL_GameShared})
    string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
    add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                       COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/StormTech -I${PROJECT_SOURCE_DIR}/Tools -I${PROJECT_SOURCE_DIR}/Shared -I${PROJECT_SOURCE_DIR}/Project -I${PROJECT_SOURCE_DIR}/Lobby -I${PROJECT_SOURCE_DIR}/External ${CLANG_COMMAND_LINE_OPTS} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                       MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                       IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
  endforeach()
endif()

add_library(GameShared STATIC ${GENERIC_SRC_GameShared} ${GENERIC_HEADER_GameShared})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_GameShared} ${GENERIC_HEADER_GameShared})

set_target_properties(GameShared PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT GameSharedCommon.h)

if(GENERATE_PCH)
  cotire(GameShared)
endif()
