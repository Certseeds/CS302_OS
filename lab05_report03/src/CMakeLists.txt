# header begin
cmake_minimum_required(VERSION 3.10.2)
project(CS302_OS_LAB05_REPORT03 LANGUAGES C)

include_directories(${CMAKE_CURRENT_LIST_DIR}/)

set (CMAKE_C_STANDARD 99)

add_executable(${PROJECT_NAME}
        ./scheduler.c
        )
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)