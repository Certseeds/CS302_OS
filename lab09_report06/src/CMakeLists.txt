cmake_minimum_required(VERSION 3.16.6)
project(lab09_report06 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
add_executable(${PROJECT_NAME}
        ./mm.cpp
        ./free_block.hpp
        ./allocated_block.hpp
        ./functions.hpp
        )
