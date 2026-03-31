cmake_minimum_required(VERSION 3.16)

add_library(pricing_ocp_lib
  src/pricing.cc
)
target_include_directories(pricing_ocp_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(pricing_ocp_lib PUBLIC nlohmann_json)

add_executable(pricing_ocp app/main.cc)
target_link_libraries(pricing_ocp PRIVATE pricing_ocp_lib)
