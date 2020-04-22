cmake_minimum_required(VERSION 3.10.2)
project(lab09_report06 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(${PROJECT_NAME}
        ./mm.cpp
        )
