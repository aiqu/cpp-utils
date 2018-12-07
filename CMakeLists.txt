cmake_minimum_required(VERSION 3.1)

project(cpp-utils VERSION 0.1 LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wl,--no-undefined -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O2 -g")
set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")

set(namespace ${PROJECT_NAME})
set(include_install_dir "${PROJECT_NAME}")

option(BUILD_TEST "Build test binary" OFF)

add_library(timer
  src/timer.cc
)
target_include_directories(timer
 PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:${include_install_dir}>
)

if (BUILD_TEST)
  add_executable(test_timer
    test/timer.cc
  )
  target_link_libraries(test_timer
  PUBLIC
    timer
  )
endif()
