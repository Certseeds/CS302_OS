# header begin
cmake_minimum_required(VERSION 3.10.2)
project(CS302_OS_lab05 LANGUAGES C)
set(CMAKE_C_STANDARD 11)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(OpenMP REQUIRED)

set(dependenciesOfMain openmp1 openmp2 thread)
foreach (elementName IN LISTS dependenciesOfMain)
    add_executable(${PROJECT_NAME}_${elementName} ${CMAKE_CURRENT_SOURCE_DIR}/${elementName}.c)
endforeach ()
unset(dependenciesOfMain)

if (OpenMP_C_FOUND)
    target_link_libraries(${PROJECT_NAME}_openmp1 PUBLIC OpenMP::OpenMP_CXX)
    target_link_libraries(${PROJECT_NAME}_openmp2 PUBLIC OpenMP::OpenMP_CXX)
endif ()

target_link_libraries(${PROJECT_NAME}_thread PUBLIC Threads::Threads)