cmake_minimum_required(VERSION 3.16)
project(case015_pipeline_provider_decoupling LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(case015_core
    src/build_pipeline.cc
    src/file_policy_provider.cc
    src/pipeline_runner.cc
    src/static_policy_provider.cc)

target_include_directories(case015_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(case015_app app/main.cc)
target_link_libraries(case015_app PRIVATE case015_core)
