# header begin
cmake_minimum_required(VERSION 3.10.2)
project(CS302_OS LANGUAGES C)

set (CMAKE_C_STANDARD 99)
# header end
# add library begin
#add_library(catch STATIC catch.hpp )
#SET_TARGET_PROPERTIES(catch PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(lab05_report03/src)
add_subdirectory(lab08_report05/src)
add_subdirectory(lab09_report06/src)