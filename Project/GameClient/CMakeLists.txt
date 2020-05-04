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

set(GENERIC_SRC_GameClient 
            Camera/GameCamera.cpp
            ClientComponents/PlayerComponent.refl.cpp
            ClientComponents/PlayerComponent.refl.reg.cpp
            ClientComponents/Reusable/AttachVfxComponent.refl.cpp
            ClientComponents/Reusable/AttachVfxComponent.refl.reg.cpp
            ClientComponents/Reusable/PlayAnimationComponent.refl.cpp
            ClientComponents/Reusable/PlayAnimationComponent.refl.reg.cpp
            ClientComponents/Reusable/SyncServerObjectComponent.refl.cpp
            ClientComponents/Reusable/SyncServerObjectComponent.refl.reg.cpp
            EffectLayers/CollisionDrawer.refl.cpp
            EffectLayers/CollisionDrawer.refl.reg.cpp
            GameClientCommon.cpp
            GameClientController.refl.cpp
            GameClientInstanceContainer.cpp
            GameClientInstanceResources.cpp
            GameClientLevelLoader.cpp
            GameClientSystems.cpp
            GameContainer.cpp
            GameServerEventResponder.cpp
            Input/GameClientInputManager.cpp
            Modes/GameMode.cpp
            Modes/GameModeConnectingGame.cpp
            Modes/GameModeConnectingLobby.cpp
            Modes/GameModeEndGame.cpp
            Modes/GameModeFindingMatch.cpp
            Modes/GameModeJoinPrivateGame.cpp
            Modes/GameModeLoadingGlobal.cpp
            Modes/GameModeLocalMultiplayer.cpp
            Modes/GameModeLogo.cpp
            Modes/GameModeMainMenu.cpp
            Modes/GameModeMapSettings.cpp
            Modes/GameModeNameSelect.cpp
            Modes/GameModeOfflineStaging.cpp
            Modes/GameModeOnlineBase.cpp
            Modes/GameModeOnlineGameplay.cpp
            Modes/GameModeOnlineStaging.cpp
            Modes/GameModePlayOnline.cpp
            Modes/GameModePlaylistMenu.cpp
            Modes/GameModeSinglePlayerBots.cpp
            Modes/GameModeStagingBase.cpp
            Modes/GameModeTutorial.cpp
            Network/GameClientEntitySync.cpp
            Network/GameClientLatencyChecker.cpp
            Network/GameNetworkClient.cpp
            Save/GameClientSave.cpp
            Shaders/GameShaders.cpp
            UI/GameClientUIManager.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_GameClient 
            Camera/GameCamera.h
            ClientComponents/PlayerComponent.refl.h
            ClientComponents/PlayerComponent.refl.meta.h
            ClientComponents/Reusable/AttachVfxComponent.refl.h
            ClientComponents/Reusable/AttachVfxComponent.refl.meta.h
            ClientComponents/Reusable/PlayAnimationComponent.refl.h
            ClientComponents/Reusable/PlayAnimationComponent.refl.meta.h
            ClientComponents/Reusable/SyncServerObjectComponent.refl.h
            ClientComponents/Reusable/SyncServerObjectComponent.refl.meta.h
            EffectLayers/CollisionDrawer.refl.h
            EffectLayers/CollisionDrawer.refl.meta.h
            GameClientCommon.h
            GameClientController.refl.h
            GameClientController.refl.meta.h
            GameClientEventSender.h
            GameClientInstanceContainer.h
            GameClientInstanceResources.h
            GameClientLevelLoader.h
            GameClientSystems.h
            GameContainer.h
            GameServerEventResponder.h
            Input/GameClientInputManager.h
            Modes/GameMode.h
            Modes/GameModeConnectingGame.h
            Modes/GameModeConnectingLobby.h
            Modes/GameModeEndGame.h
            Modes/GameModeFindingMatch.h
            Modes/GameModeJoinPrivateGame.h
            Modes/GameModeLoadingGlobal.h
            Modes/GameModeLocalMultiplayer.h
            Modes/GameModeLogo.h
            Modes/GameModeMainMenu.h
            Modes/GameModeMapSettings.h
            Modes/GameModeNameSelect.h
            Modes/GameModeOfflineStaging.h
            Modes/GameModeOnlineBase.h
            Modes/GameModeOnlineGameplay.h
            Modes/GameModeOnlineStaging.h
            Modes/GameModePlayOnline.h
            Modes/GameModePlaylistMenu.h
            Modes/GameModeSinglePlayerBots.h
            Modes/GameModeStagingBase.h
            Modes/GameModeTutorial.h
            Network/GameClientEntitySync.h
            Network/GameClientLatencyChecker.h
            Network/GameNetworkClient.h
            Save/GameClientSave.h
            Save/GameClientSaveFileData.refl.h
            Save/GameClientSaveFileData.refl.meta.h
            Shaders/GameShaders.h
            UI/GameClientUIData.refl.h
            UI/GameClientUIData.refl.meta.h
            UI/GameClientUIManager.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_GameClient 
            ClientComponents/PlayerComponent.refl.h
            ClientComponents/Reusable/AttachVfxComponent.refl.h
            ClientComponents/Reusable/PlayAnimationComponent.refl.h
            ClientComponents/Reusable/SyncServerObjectComponent.refl.h
            EffectLayers/CollisionDrawer.refl.h
            GameClientController.refl.h
            Save/GameClientSaveFileData.refl.h
            UI/GameClientUIData.refl.h
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(${PROJECT_SOURCE_DIR}/External/Windows)
  set(PLATFORM_SRC_GameClient 
            )

set(PLATFORM_HEADER_GameClient 
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(${PROJECT_SOURCE_DIR}/External/Web)
  set(PLATFORM_SRC_GameClient 
            )

set(PLATFORM_HEADER_GameClient 
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/IOS)
  set(PLATFORM_SRC_GameClient 
            )

set(PLATFORM_HEADER_GameClient 
            )
endif()
if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_GameClient 
            )

set(PLATFORM_HEADER_GameClient 
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(${PROJECT_SOURCE_DIR}/External/Android)
  set(PLATFORM_SRC_GameClient 
            )

set(PLATFORM_HEADER_GameClient 
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(${PROJECT_SOURCE_DIR}/External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_GameClient 
            )

set(PLATFORM_HEADER_GameClient 
            )
endif()


if(GENERATE_REFL)
  foreach(REFL_FILE ${GENERIC_REFL_GameClient})
    string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
    add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                       COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/StormTech -I${PROJECT_SOURCE_DIR}/Tools -I${PROJECT_SOURCE_DIR}/Shared -I${PROJECT_SOURCE_DIR}/Project -I${PROJECT_SOURCE_DIR}/Lobby -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                       MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                       IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
  endforeach()
endif()

add_library(GameClient STATIC ${GENERIC_SRC_GameClient} ${PLATFORM_SRC_GameClient}
            ${GENERIC_HEADER_GameClient} ${PLATFORM_HEADER_GameClient})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_GameClient} ${PLATFORM_SRC_GameClient}
            ${GENERIC_HEADER_GameClient} ${PLATFORM_HEADER_GameClient})

set_target_properties(GameClient PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT GameClientCommon.h)

if(GENERATE_PCH)
  cotire(GameClient)
endif()
