cmake_minimum_required(VERSION 3.16)
project(case019_ranking_explainability_boundary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(case019_ranking
    src/ranker.cc
)

target_include_directories(case019_ranking PUBLIC src)

target_compile_options(case019_ranking PRIVATE -Wall -Wextra -Wpedantic)

add_executable(case019_app
    app/main.cc
)

target_link_libraries(case019_app PRIVATE case019_ranking)
