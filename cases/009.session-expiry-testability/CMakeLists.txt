cmake_minimum_required(VERSION 3.16)
project(case009_session_expiry_testability LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(case009_lib
    src/session_manager.cc
    src/time_source.cc)

target_include_directories(case009_lib PUBLIC src)

target_compile_options(case009_lib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(case009_app app/main.cc)
target_link_libraries(case009_app PRIVATE case009_lib)
