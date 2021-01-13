# header begin
cmake_minimum_required(VERSION 3.10.2)
project(CS302_OS_lab03 LANGUAGES C)
set(CMAKE_C_STANDARD 11)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/util.cmake)

ADDEXEC(ABC)
ADDEXEC(exec)
ADDEXEC(fork)
ADDEXEC(getpid)
ADDEXEC(nwait)
ADDEXEC(pfork)
ADDEXEC(pipe)
ADDEXEC(signal)
ADDEXEC(wait)
