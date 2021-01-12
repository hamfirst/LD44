cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}
                    ${PROJECT_SOURCE_DIR}/External
                    ${PROJECT_SOURCE_DIR}/StormTech
                    ${PROJECT_SOURCE_DIR}/Tools
                    ${PROJECT_SOURCE_DIR}/Shared
                    ${PROJECT_SOURCE_DIR}/Project
                    ${PROJECT_SOURCE_DIR}/Lobby)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
endif()

set(GENERIC_SRC_Lobby 
            BanList.refl.cpp
            Bot.refl.cpp
            BotConnection.refl.cpp
            BotEndpoint.cpp
            BuiltInChannel.refl.cpp
            Channel.refl.cpp
            CommandParse.cpp
            CoordinatorState.cpp
            Game.refl.cpp
            GameData.refl.cpp
            GameList.refl.cpp
            GameServerConnection.refl.cpp
            GameServerEndpoint.cpp
            LoadBalancer.cpp
            LobbyLevelList.refl.cpp
            Matchmaker.refl.cpp
            NodeState.cpp
            Rewards.refl.cpp
            ServerManager.refl.cpp
            Squad.refl.cpp
            SteamOpenIdValidatorPage.cpp
            User.refl.cpp
            UserConnection.refl.cpp
            UserEndpoint.cpp
            WelcomeInfo.refl.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_Lobby 
            BanList.refl.h
            Bot.refl.h
            BotConnection.refl.h
            BotEndpoint.h
            BotMessages.refl.h
            BuiltInChannel.refl.h
            Channel.refl.h
            CommandParse.h
            CoordinatorState.h
            DataTypes.h
            Game.refl.h
            GameData.refl.h
            GameList.refl.h
            GameServerConnection.refl.h
            GameServerEndpoint.h
            GameServerMessages.refl.h
            GooglePlatform.refl.h
            LoadBalancer.h
            LobbyConfig.h
            LobbyLevelList.refl.h
            Matchmaker.refl.h
            NodeState.h
            Rewards.refl.h
            ServerManager.refl.h
            Squad.refl.h
            SteamOpenIdValidatorPage.h
            SteamServerMessages.refl.h
            User.refl.h
            UserConnection.refl.h
            UserConnectionMessages.refl.h
            UserEndpoint.h
            WelcomeInfo.refl.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_Lobby 
            BanList.refl.h
            Bot.refl.h
            BotConnection.refl.h
            BotMessages.refl.h
            BuiltInChannel.refl.h
            Channel.refl.h
            Game.refl.h
            GameData.refl.h
            GameList.refl.h
            GameServerConnection.refl.h
            GameServerMessages.refl.h
            GooglePlatform.refl.h
            LobbyLevelList.refl.h
            Matchmaker.refl.h
            Rewards.refl.h
            ServerManager.refl.h
            Squad.refl.h
            SteamServerMessages.refl.h
            User.refl.h
            UserConnection.refl.h
            UserConnectionMessages.refl.h
            WelcomeInfo.refl.h
            #REFL_PLACEHOLDER
            )

if(GENERATE_REFL)
  foreach(REFL_FILE ${GENERIC_REFL_Lobby})
    string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
    add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                       COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/StormTech -I${PROJECT_SOURCE_DIR}/Tools -I${PROJECT_SOURCE_DIR}/Shared -I${PROJECT_SOURCE_DIR}/Project -I${PROJECT_SOURCE_DIR}/Lobby -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                       MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                       IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
  endforeach()
endif()

add_library(Lobby STATIC ${GENERIC_SRC_Lobby} ${GENERIC_HEADER_Lobby})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_Lobby} ${GENERIC_HEADER_Lobby})

