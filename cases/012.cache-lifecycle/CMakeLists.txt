cmake_minimum_required(VERSION 3.16)
project(case012_cache_lifecycle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(case012_lib
    src/summary_engine.cc
    src/inventory_report_service.cc)

target_include_directories(case012_lib PUBLIC src)
target_compile_options(case012_lib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(case012_app app/main.cc)
target_link_libraries(case012_app PRIVATE case012_lib)
