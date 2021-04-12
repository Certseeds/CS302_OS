# header begin
cmake_minimum_required(VERSION 3.10.2)
project(CS302_OS_report_04_lab06 LANGUAGES C)
set(CMAKE_C_STANDARD 11)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME}_src ${CMAKE_CURRENT_SOURCE_DIR}/Main_file.c)
target_link_libraries(${PROJECT_NAME}_src PUBLIC Threads::Threads)
