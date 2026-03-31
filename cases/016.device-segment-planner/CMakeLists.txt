cmake_minimum_required(VERSION 3.16)
project(case016_device_segment_planner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(case016_lib
    src/pipeline_config.cc
    src/execution_plan.cc
    src/pipeline_runner.cc)

target_include_directories(case016_lib PUBLIC src)

add_executable(case016_app app/main.cc)
target_link_libraries(case016_app PRIVATE case016_lib)
