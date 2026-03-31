cmake_minimum_required(VERSION 3.16)
project(case007_ml_lsp_feature_transform LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(case007_core
    src/clamp_transform.cc
    src/identity_transform.cc
    src/l2_normalize_transform.cc
    src/feature_pipeline.cc
    src/transform_batch.cc
    src/transform_chain.cc
    src/transform_factory.cc
)

target_include_directories(case007_core PUBLIC src)

add_executable(case007_app app/main.cc)
target_link_libraries(case007_app PRIVATE case007_core)
