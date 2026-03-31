cmake_minimum_required(VERSION 3.16)

project(case021_inline_filter_entrypoint_reuse LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(case021_lib
  src/filter_parser.cc
  src/filter_rule.cc
  src/filter_validation.cc
)

target_include_directories(case021_lib
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(case021_app
  app/main.cc
)

target_link_libraries(case021_app
  PRIVATE
    case021_lib
)
