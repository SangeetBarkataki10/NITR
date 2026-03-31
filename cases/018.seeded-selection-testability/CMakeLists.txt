cmake_minimum_required(VERSION 3.16)
project(case018_seeded_selection_testability LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(case018_core
  src/rules.cc
  src/selector.cc
  src/sampler_v1.cc
)

target_include_directories(case018_core
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(case018_app
  app/main.cc
)
target_link_libraries(case018_app PRIVATE case018_core)
