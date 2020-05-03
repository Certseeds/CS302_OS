# header begin
cmake_minimum_required(VERSION 3.10.2)
project(CS302_OS LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
# header end
# add library begin
#add_library(catch STATIC catch.hpp )
#SET_TARGET_PROPERTIES(catch PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(lab05_report03/src)
add_subdirectory(lab08_report05/src)
add_subdirectory(lab09_report06/src)