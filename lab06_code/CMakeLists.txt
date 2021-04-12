# header begin
cmake_minimum_required(VERSION 3.10.2)
project(CS302_OS_lab06 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(dependencies milk producer_consumer semaphore)
foreach (elementName IN LISTS dependencies)
    add_executable(${PROJECT_NAME}_${elementName} ${CMAKE_CURRENT_SOURCE_DIR}/${elementName}.cpp)
    target_link_libraries(${PROJECT_NAME}_${elementName} PUBLIC Threads::Threads)
    MESSAGE(STATUS "${PROJECT_NAME}_${elementName} from ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_ORDER}_${elementName}.cpp")
endforeach ()
unset(dependencies)
