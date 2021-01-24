cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ../../External)

add_executable(stormrefl
  StormReflOutput.cpp
  main.cpp)

target_compile_options(stormrefl PUBLIC "-fno-rtti" "-O3")
target_link_libraries(stormrefl -Wl,--whole-archive pthread -Wl,--no-whole-archive)
target_link_libraries(stormrefl ncurses stdc++fs z rt m c dl)

set (CLANG_SEARCH_PATHS
  ${CMAKE_BINARY_DIR}/${CLANG_FILE}
  ${CMAKE_BINARY_DIR}/${CLANG_FILE}/lib/cmake
  ${CMAKE_BINARY_DIR}/${CLANG_FILE}/lib/cmake/llvm
  ${CMAKE_BINARY_DIR}/${CLANG_FILE}/lib/cmake/clang
  ${CMAKE_BINARY_DIR}/${CLANG_FILE}/share/clang/cmake/
  ${CMAKE_BINARY_DIR}/${CLANG_FILE}/share/llvm/cmake/
  )

find_package(LLVM REQUIRED CONFIG
  PATHS ${CLANG_SEARCH_PATHS}
  NO_DEFAULT_PATH)
find_package(Clang REQUIRED CONFIG
  PATHS ${CLANG_SEARCH_PATHS}
  NO_DEFAULT_PATH)

target_include_directories(stormrefl PUBLIC ${LLVM_INCLUDE_DIRS})
target_link_libraries(stormrefl LLVMSupport clangTooling)

