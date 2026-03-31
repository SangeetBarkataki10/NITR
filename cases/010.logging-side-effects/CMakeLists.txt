cmake_minimum_required(VERSION 3.16)
project(case010_logging_side_effects LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(case010_lib
    src/audit_logger.cc
    src/loan_policy.cc
    src/loan_review_service.cc)

target_include_directories(case010_lib PUBLIC src)
target_compile_options(case010_lib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(case010_app app/main.cc)
target_link_libraries(case010_app PRIVATE case010_lib)
