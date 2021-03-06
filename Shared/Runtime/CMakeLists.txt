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

set(GENERIC_SRC_Runtime 
            Anchor/AnchorDef.refl.cpp
            Anchor/AnchorTypeDatabase.cpp
            Asset/Asset.cpp
            Atlas/AtlasDef.refl.cpp
            Atlas/AtlasResource.cpp
            BinaryResource/BinaryResourceBase.cpp
            BinaryResource/BinaryResourceManager.cpp
            BinaryResource/BinaryResourceReferenceBase.cpp
            BinaryResource/GenericBinaryResource.cpp
            ClientComponent/ClientComponentInitData.refl.cpp
            ClientComponent/ClientComponentInitDataTypeDatabase.cpp
            ClientEntity/ClientEntityDef.refl.cpp
            ClientEntity/ClientEntityResource.cpp
            Collision/CollisionDatabase.cpp
            Collision/DynamicCollisionDatabase.cpp
            Collision/StaticCollisionDatabase.cpp
            Config/ConfigManager.cpp
            DocumentResource/DocumentResourceBase.cpp
            DocumentResource/DocumentResourceManager.cpp
            DocumentResource/DocumentResourceReferenceBase.cpp
            FrameData/FrameData.refl.cpp
            FrameData/FrameDataExtract.cpp
            Map/MapCollision.cpp
            Map/MapDef.refl.cpp
            Map/MapEffectLayerDef.refl.cpp
            Map/MapEffectLayerTypeDatabase.cpp
            Map/MapHandles.refl.cpp
            Map/MapPropertiesDef.refl.cpp
            Map/MapPropertiesTypeDatabase.cpp
            Map/MapResource.cpp
            Mover/Mover.cpp
            Path/PathDef.refl.cpp
            Path/PathTypeDatabase.cpp
            Runtime.cpp
            RuntimeCommon.cpp
            Script/ScriptResource.cpp
            ServerEntity/ServerEntity.cpp
            ServerEntity/ServerEntityDef.refl.cpp
            ServerEntity/ServerEntityEventDispatch.cpp
            ServerEntity/ServerEntityEventSystem.cpp
            ServerEntity/ServerEntityHandle.cpp
            ServerEntity/ServerEntityInitData.refl.cpp
            ServerEntity/ServerEntityInitDataTypeDatabase.cpp
            ServerEntity/ServerEntityManager.cpp
            ServerEntity/ServerEntityResource.cpp
            ServerEntity/ServerEntitySerialize.cpp
            ServerEntity/ServerEntitySystem.cpp
            ServerEntity/ServerObjectUpdate.cpp
            Sprite/SpriteDef.refl.cpp
            Sprite/SpriteResource.cpp
            SpriteBase/SpriteAnimationEventDef.refl.cpp
            SpriteBase/SpriteAnimationEventTypeDatabase.cpp
            SpriteBase/SpriteBaseDef.refl.cpp
            TileSheet/TileSheetDef.refl.cpp
            TileSheet/TileSheetResource.cpp
            UI/UIDef.refl.cpp
            UI/UIResource.cpp
            VisualEffect/VisualEffectDef.refl.cpp
            VisualEffect/VisualEffectResource.cpp
            Volume/VolumeDef.refl.cpp
            Volume/VolumeTypeDatabase.cpp
            #CPP_PLACEHOLDER
            )

set(GENERIC_HEADER_Runtime 
            Anchor/AnchorDef.refl.h
            Anchor/AnchorTypeDatabase.h
            Anchor/AnchorTypeRegister.h
            Animation/AnimationState.h
            Asset/Asset.h
            Atlas/AtlasDef.refl.h
            Atlas/AtlasResource.h
            BinaryResource/BinaryResourceBase.h
            BinaryResource/BinaryResourceLoader.h
            BinaryResource/BinaryResourceManager.h
            BinaryResource/BinaryResourcePtr.h
            BinaryResource/BinaryResourceReference.h
            BinaryResource/BinaryResourceReferenceBase.h
            BinaryResource/GenericBinaryResource.h
            ClientComponent/ClientComponentInitData.refl.h
            ClientComponent/ClientComponentInitDataTypeDatabase.h
            ClientComponent/ClientComponentInitDataTypeDatabaseRegister.h
            ClientEntity/ClientEntityDef.refl.h
            ClientEntity/ClientEntityResource.h
            Collision/CollisionDatabase.h
            Collision/CollisionDatabaseResult.h
            Collision/DynamicCollisionDatabase.h
            Collision/IntersectionDatabase.h
            Collision/StaticCollisionDatabase.h
            Config/ConfigList.h
            Config/ConfigManager.h
            Config/ConfigRegistrationMacros.h
            Config/ConfigResource.h
            DocumentResource/DocumentResourceBase.h
            DocumentResource/DocumentResourceLoader.h
            DocumentResource/DocumentResourceManager.h
            DocumentResource/DocumentResourcePtr.h
            DocumentResource/DocumentResourceReference.h
            DocumentResource/DocumentResourceReferenceBase.h
            Event/Event.h
            Event/EventDispatcher.h
            Event/EventHandler.h
            Event/EventSystem.h
            FrameData/FrameData.refl.h
            FrameData/FrameDataExtract.h
            GenericResource/GenericResource.h
            Map/MapCollision.h
            Map/MapDef.refl.h
            Map/MapEffectLayerDef.refl.h
            Map/MapEffectLayerTypeDatabase.h
            Map/MapEffectLayerTypeRegister.h
            Map/MapHandles.refl.h
            Map/MapMetaExtractor.h
            Map/MapPropertiesDef.refl.h
            Map/MapPropertiesTypeDatabase.h
            Map/MapPropertiesTypeRegister.h
            Map/MapResource.h
            Map/MapTile.h
            Map/MapTileJson.h
            Mover/Mover.h
            Path/PathDef.refl.h
            Path/PathTypeDatabase.h
            Path/PathTypeRegister.h
            Runtime.h
            RuntimeCommon.h
            Script/ScriptResource.h
            ServerEntity/ServerEntity.h
            ServerEntity/ServerEntityComponent.h
            ServerEntity/ServerEntityComponentFuncs.h
            ServerEntity/ServerEntityComponentSerialize.h
            ServerEntity/ServerEntityDef.refl.h
            ServerEntity/ServerEntityEventDispatch.h
            ServerEntity/ServerEntityEventRegister.h
            ServerEntity/ServerEntityEventSystem.h
            ServerEntity/ServerEntityHandle.h
            ServerEntity/ServerEntityInitData.refl.h
            ServerEntity/ServerEntityInitDataTypeDatabase.h
            ServerEntity/ServerEntityManager.h
            ServerEntity/ServerEntityMetaFuncs.h
            ServerEntity/ServerEntityOverlapRegistrationMacros.h
            ServerEntity/ServerEntityRegistrationMacros.h
            ServerEntity/ServerEntityResource.h
            ServerEntity/ServerEntitySerialize.h
            ServerEntity/ServerEntitySystem.h
            ServerEntity/ServerEntityTypeInfo.h
            ServerEntity/ServerObjectUpdate.h
            ServerEntity/ServerTypesJson.h
            ServerEntity/ServerTypesNet.h
            Sprite/SpriteDef.refl.h
            Sprite/SpriteResource.h
            SpriteBase/SpriteAnimationEventDef.refl.h
            SpriteBase/SpriteAnimationEventRegister.h
            SpriteBase/SpriteAnimationEventTypeDatabase.h
            SpriteBase/SpriteBaseDef.refl.h
            TileSheet/TileSheetDef.refl.h
            TileSheet/TileSheetResource.h
            UI/UIDef.refl.h
            UI/UIResource.h
            VisualEffect/VisualEffectDef.refl.h
            VisualEffect/VisualEffectResource.h
            Volume/VolumeDef.refl.h
            Volume/VolumeTypeDatabase.h
            Volume/VolumeTypeRegister.h
            #HEADER_PLACEHOLDER
            )

set(GENERIC_REFL_Runtime 
            Anchor/AnchorDef.refl.h
            Atlas/AtlasDef.refl.h
            ClientComponent/ClientComponentInitData.refl.h
            ClientEntity/ClientEntityDef.refl.h
            FrameData/FrameData.refl.h
            Map/MapDef.refl.h
            Map/MapEffectLayerDef.refl.h
            Map/MapHandles.refl.h
            Map/MapPropertiesDef.refl.h
            Path/PathDef.refl.h
            ServerEntity/ServerEntityDef.refl.h
            ServerEntity/ServerEntityInitData.refl.h
            Sprite/SpriteDef.refl.h
            SpriteBase/SpriteAnimationEventDef.refl.h
            SpriteBase/SpriteBaseDef.refl.h
            TileSheet/TileSheetDef.refl.h
            UI/UIDef.refl.h
            VisualEffect/VisualEffectDef.refl.h
            Volume/VolumeDef.refl.h
            #REFL_PLACEHOLDER
            )

if(GENERATE_REFL)
  foreach(REFL_FILE ${GENERIC_REFL_Runtime})
    string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
    add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                       COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/StormTech -I${PROJECT_SOURCE_DIR}/Tools -I${PROJECT_SOURCE_DIR}/Shared -I${PROJECT_SOURCE_DIR}/Project -I${PROJECT_SOURCE_DIR}/Lobby -I${PROJECT_SOURCE_DIR}/External ${CLANG_COMMAND_LINE_OPTS} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                       MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                       IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
  endforeach()
endif()

add_library(Runtime STATIC ${GENERIC_SRC_Runtime} ${GENERIC_HEADER_Runtime})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_Runtime} ${GENERIC_HEADER_Runtime})

set_target_properties(Runtime PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT RuntimeCommon.h)

if(GENERATE_PCH)
  cotire(Runtime)
endif()
