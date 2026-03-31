cmake_minimum_required(VERSION 3.16)

# ---- SRP impl library (NO legacy) ----
add_library(add_lib
  src/add.cc
)

target_include_directories(add_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(add_lib)

# ---- main binary (SRP path only) ----
add_executable(add app/main.cc)
target_link_libraries(add PRIVATE add_lib)
