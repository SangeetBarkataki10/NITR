cmake_minimum_required(VERSION 3.16)

# ---- SRP impl library (NO legacy) ----
add_library(cv_srp_lib
  src/io_json.cc
  src/math_linalg.cc
  src/math_sampson.cc
  src/normalize.cc
  src/estimator_e.cc
  src/scoring.cc
  src/policy.cc
  src/pipeline.cc
)

target_include_directories(cv_srp_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(cv_srp_lib PUBLIC nlohmann_json)

# ---- main binary (SRP path only) ----
add_executable(cv_srp app/main.cc)
target_link_libraries(cv_srp PRIVATE cv_srp_lib)
