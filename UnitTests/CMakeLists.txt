 
cmake_minimum_required(VERSION 3.0)

include_directories(${PROJECT_SOURCE_DIR}/External/gtest/googletest/include)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/External
  ${PROJECT_SOURCE_DIR}/StormTech
  ${PROJECT_SOURCE_DIR}/Tools
  ${PROJECT_SOURCE_DIR}/Shared
  ${PROJECT_SOURCE_DIR}/Project
  ${PROJECT_SOURCE_DIR}/Lobby)

add_subdirectory(StormNetSysTest)

add_executable(StormNetSysTestExe ../Dummy.cpp)
target_link_libraries(StormNetSysTestExe StormNetSysTest StormNetSys StormNet gtest_main)
set_target_properties(StormNetSysTestExe PROPERTIES FOLDER UnitTests)

