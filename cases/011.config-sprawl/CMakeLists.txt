cmake_minimum_required(VERSION 3.16)
project(case011_config_sprawl CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(case011_lib
    src/report_renderer.cc
    src/report_types.cc)

target_include_directories(case011_lib PUBLIC src)

add_executable(case011_app
    app/main.cc)
target_link_libraries(case011_app PRIVATE case011_lib)
