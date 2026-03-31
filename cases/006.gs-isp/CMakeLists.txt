cmake_minimum_required(VERSION 3.16)
project(case006_gs_isp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(case006_lib
  src/project_and_bin.cc
  src/sort_hits.cc
  src/eval_shading.cc
  src/composite.cc
  src/pipeline.cc)

target_include_directories(case006_lib PUBLIC src)

target_compile_options(case006_lib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(case006_app app/main.cc)
target_link_libraries(case006_app PRIVATE case006_lib)
