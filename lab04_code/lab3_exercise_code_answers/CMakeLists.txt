# header begin
cmake_minimum_required(VERSION 3.10.2)
project(CS302_OS_lab03_exercise_code_answers LANGUAGES C)
set(CMAKE_C_STANDARD 11)

set(dependencies fork_detail fork_exec fork_exec2 mq_read mq_write
        share_file_fwrite share_file_write time_example1 time_example2 time_example3 wait_exit)
foreach (elementName IN LISTS dependencies)
    add_executable(${PROJECT_NAME}_${elementName} ${CMAKE_CURRENT_SOURCE_DIR}/${elementName}.c)
    MESSAGE(STATUS "${PROJECT_NAME}_${elementName} from ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_ORDER}_${elementName}.cpp")
endforeach ()
unset(dependencies)