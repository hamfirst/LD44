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
            BehaviorTree/Conditionals/IsDeadBotConditional.refl.cpp
            BehaviorTree/Conditionals/IsDeadBotConditional.refl.reg.cpp
            BehaviorTree/States/MoveForTimeBotState.refl.cpp
            BehaviorTree/States/MoveForTimeBotState.refl.reg.cpp
            BehaviorTree/States/PlayAnimationBotState.refl.cpp
            BehaviorTree/States/PlayAnimationBotState.refl.reg.cpp
            BehaviorTree/States/PlayAnimationForTimeBotState.refl.cpp
            BehaviorTree/States/PlayAnimationForTimeBotState.refl.reg.cpp
            GameEventReconciler.cpp
            GameLevelList.cpp
            GameLogicContainer.cpp
            GamePlayList.cpp
            GameSharedCommon.cpp
            GameStageManager.cpp
            GameWebrtc.cpp
            Systems/CVCPushSystem.cpp
            Systems/GameLogicSystems.cpp
            Systems/GameServerObjectOverlapSystem.cpp
            Systems/TargetDatabase.cpp
            BehaviorTree/Conditionals/IsAlertedBotConditional.refl.cpp
            BehaviorTree/Conditionals/IsAlertedBotConditional.refl.reg.cpp
            BehaviorTree/Conditionals/IsBeingEatenBotConditional.refl.cpp
            BehaviorTree/Conditionals/IsBeingEatenBotConditional.refl.reg.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_GameShared 
            BehaviorTree/BehaviorTree.h
            BehaviorTree/BehaviorTreeSerialize.h
            BehaviorTree/BehaviorTreeTypeDatabase.h
            BehaviorTree/Conditionals/IsDeadBotConditional.refl.h
            BehaviorTree/Conditionals/IsDeadBotConditional.refl.meta.h
            BehaviorTree/States/MoveForTimeBotState.refl.h
            BehaviorTree/States/MoveForTimeBotState.refl.meta.h
            BehaviorTree/States/PlayAnimationBotState.refl.h
            BehaviorTree/States/PlayAnimationBotState.refl.meta.h
            BehaviorTree/States/PlayAnimationForTimeBotState.refl.h
            BehaviorTree/States/PlayAnimationForTimeBotState.refl.meta.h
            GameEventReconciler.h
            GameLevelList.h
            GameLevelListAsset.refl.h
            GameLevelListAsset.refl.meta.h
            GameLogicContainer.h
            GamePlayList.h
            GamePlayListAsset.refl.h
            GamePlayListAsset.refl.meta.h
            GameProtocol.h
            GameSharedCommon.h
            GameStageManager.h
            Systems/CVCPushSystem.h
            Systems/GameLogicSystems.h
            Systems/GameServerObjectOverlapRegistrationMacros.h
            Systems/GameServerObjectOverlapSystem.h
            Systems/TargetDatabase.h
            BehaviorTree/Conditionals/IsAlertedBotConditional.refl.h
            BehaviorTree/Conditionals/IsAlertedBotConditional.refl.meta.h
            BehaviorTree/Conditionals/IsBeingEatenBotConditional.refl.h
            BehaviorTree/Conditionals/IsBeingEatenBotConditional.refl.meta.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_GameShared 
            BehaviorTree/Conditionals/IsDeadBotConditional.refl.h
            BehaviorTree/States/MoveForTimeBotState.refl.h
            BehaviorTree/States/PlayAnimationBotState.refl.h
            BehaviorTree/States/PlayAnimationForTimeBotState.refl.h
            GameLevelListAsset.refl.h
            GamePlayListAsset.refl.h
            BehaviorTree/Conditionals/IsAlertedBotConditional.refl.h
            BehaviorTree/Conditionals/IsBeingEatenBotConditional.refl.h
            #REFL_PLACEHOLDER
            )

if(GENERATE_REFL)
  foreach(REFL_FILE ${GENERIC_REFL_GameShared})
    string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
    add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                       COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/StormTech -I${PROJECT_SOURCE_DIR}/Tools -I${PROJECT_SOURCE_DIR}/Shared -I${PROJECT_SOURCE_DIR}/Project -I${PROJECT_SOURCE_DIR}/Lobby -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
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
