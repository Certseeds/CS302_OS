# header begin
cmake_minimum_required(VERSION 3.10.2)
project(CS302_OS LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(./third_party)
include_directories(./include)

# header end
# add library begin
#add_library(catch STATIC catch.hpp )
#SET_TARGET_PROPERTIES(catch PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(lab01_code)
add_subdirectory(lab03_code)
add_subdirectory(lab05_code)
add_subdirectory(report_02_lab03)
add_subdirectory(report_03_lab05/src)
add_subdirectory(report_05_lab08/src)
add_subdirectory(report_06_lab09/src)
add_subdirectory(report_07/src)
add_subdirectory(report_08/src)