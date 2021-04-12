cmake_minimum_required(VERSION 3.10.2)
project(report_05_lab08 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_executable(${PROJECT_NAME}
        #./Banker.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Banker_Test.cpp
        )
