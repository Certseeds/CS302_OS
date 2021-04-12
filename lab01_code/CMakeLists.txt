# header begin
cmake_minimum_required(VERSION 3.10.2)
project(CS302_OS_lab01 LANGUAGES C)
set(CMAKE_C_STANDARD 11)

set(dependenciesOfMain hello opt sqrt)
foreach (elementName IN LISTS dependenciesOfMain)
    add_executable(${PROJECT_NAME}_${elementName} ${CMAKE_CURRENT_SOURCE_DIR}/${elementName}.c)
    target_link_libraries(${PROJECT_NAME}_${elementName} m)
endforeach ()
unset(dependenciesOfMain)