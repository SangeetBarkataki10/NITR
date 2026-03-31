cmake_minimum_required(VERSION 3.16)
project(case017_active_snapshot_lifecycle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(case017_lib
  src/query_service.cc
  src/snapshot_store.cc
)

target_include_directories(case017_lib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(case017_app
  app/main.cc
)
target_link_libraries(case017_app PRIVATE case017_lib)
