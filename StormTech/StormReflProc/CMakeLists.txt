cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External)

set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_StormReflProc
  StormReflOutput.cpp
  StaticLibs.cpp
  main.cpp
  #CPP_PLACEHOLDER
  )
set(GENERIC_HEADER_StormReflProc
  StormReflOutput.h
  #HEADER_PLACEHOLDER
  )


add_library(StormReflProc ${GENERIC_SRC_StormReflProc} ${GENERIC_HEADER_StormReflProc})
