# header begin
cmake_minimum_required(VERSION 3.10.2)
project(CS302_OS_lab05 LANGUAGES C)
set(CMAKE_C_STANDARD 11)
include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/util.cmake)

ADDEXEC(openmp1)
ADDEXEC(openmp2)
ADDEXEC(thread)

find_package(OpenMP REQUIRED)
if (OpenMP_CXX_FOUND)
    target_link_libraries(${PROJECT_NAME}_openmp1 PUBLIC OpenMP::OpenMP_CXX)
    target_link_libraries(${PROJECT_NAME}_openmp2 PUBLIC OpenMP::OpenMP_CXX)
endif ()


