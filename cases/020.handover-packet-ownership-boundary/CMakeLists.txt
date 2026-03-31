cmake_minimum_required(VERSION 3.16)

project(case020_handover_packet_ownership_boundary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(case020_lib
    src/handover_packet.cc
    src/handover_packet_preview.cc
    src/handover_packet_writer.cc
    src/shift_tracker.cc
)

target_include_directories(case020_lib PUBLIC src)

add_executable(case020_app app/main.cc)
target_link_libraries(case020_app PRIVATE case020_lib)
