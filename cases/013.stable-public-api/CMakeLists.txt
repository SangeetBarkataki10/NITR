cmake_minimum_required(VERSION 3.16)
project(case013_stable_public_api LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(case013_lib
    src/library_catalog.cc
)
target_include_directories(case013_lib PUBLIC src)

add_executable(case013_app app/main.cc)
target_link_libraries(case013_app PRIVATE case013_lib)
