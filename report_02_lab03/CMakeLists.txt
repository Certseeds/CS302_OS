# header begin
cmake_minimum_required(VERSION 3.10.2)
project(CS302_OS_report_02_lab03 LANGUAGES C)
set(CMAKE_C_STANDARD 11)

set(dependenciesOfMain fork pipe process signal sys)
foreach (elementName IN LISTS dependenciesOfMain)
    add_executable(${PROJECT_NAME}_${elementName} ${CMAKE_CURRENT_SOURCE_DIR}/${elementName}.c)
endforeach ()
unset(dependenciesOfMain)