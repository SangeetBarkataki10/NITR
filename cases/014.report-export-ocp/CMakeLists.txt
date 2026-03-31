cmake_minimum_required(VERSION 3.16)
project(case014_report_export_ocp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIB_SOURCES
  src/text_report_exporter.cc
  src/csv_report_exporter.cc
  src/report_export_service.cc
  src/exporter_factory.cc
)

add_library(case014_lib ${LIB_SOURCES})
target_include_directories(case014_lib PUBLIC src)

add_executable(report_export_app app/main.cc)
target_link_libraries(report_export_app PRIVATE case014_lib)
