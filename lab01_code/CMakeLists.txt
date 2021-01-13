# header begin
cmake_minimum_required(VERSION 3.10.2)
project(CS302_OS_lab01 LANGUAGES C)
set(CMAKE_C_STANDARD 11)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/util.cmake)

ADDEXEC(hello)
ADDEXEC(opt)
ADDEXEC(sqrt)
