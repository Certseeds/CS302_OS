# header begin
cmake_minimum_required(VERSION 3.10.2)
project(CS302_OS_lab03 LANGUAGES C)
set(CMAKE_C_STANDARD 11)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/util.cmake)

set(dependenciesOfMain ABC exec fork getpid nwait pfork pipe signal wait)
foreach (elementName IN LISTS dependenciesOfMain)
    ADDEXEC(${elementName})
endforeach ()
unset(dependenciesOfMain)