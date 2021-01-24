cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_ogg 
            bitwise.c
            framing.c
            #CPP_PLACEHOLDER
            )
set(GENERIC_HEADER_ogg 
            config_types.h
            ogg.h
            os_types.h
            #HEADER_PLACEHOLDER
            )
set(GENERIC_REFL_ogg 
            #REFL_PLACEHOLDER
            )

if (MSVC)
  add_definitions(-D_WINDOWS)
  include_directories(${PROJECT_SOURCE_DIR}/External/Windows)
  set(PLATFORM_SRC_ogg 
            )

set(PLATFORM_HEADER_ogg 
            )
endif()
if (WEB)
  add_definitions(-D_WEB)
  include_directories(${PROJECT_SOURCE_DIR}/External/Web)
  set(PLATFORM_SRC_ogg 
            )

set(PLATFORM_HEADER_ogg 
            )
endif()
if (IOS)
  add_definitions(-D_IOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/IOS)
  set(PLATFORM_SRC_ogg 
            )

set(PLATFORM_HEADER_ogg 
            )
endif()
if (APPLE AND NOT IOS)
  add_definitions(-D_MACOS)
  include_directories(${PROJECT_SOURCE_DIR}/External/MacOS)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_ogg 
            )

set(PLATFORM_HEADER_ogg 
            )
endif()
if (ANDROID)
  add_definitions(-D_ANDROID)
  include_directories(${PROJECT_SOURCE_DIR}/External/Android)
  set(PLATFORM_SRC_ogg 
            )

set(PLATFORM_HEADER_ogg 
            )
endif()
if (UNIX AND NOT APPLE)
  add_definitions(-D_LINUX)
  include_directories(${PROJECT_SOURCE_DIR}/External/Linux)
  include_directories(/usr/include/freetype2)
  set(PLATFORM_SRC_ogg 
            )

set(PLATFORM_HEADER_ogg 
            )
endif()

add_library(ogg STATIC ${GENERIC_SRC_ogg} ${PLATFORM_SRC_ogg}
            ${GENERIC_HEADER_ogg} ${PLATFORM_HEADER_ogg})