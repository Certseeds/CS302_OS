function(ADDEXEC EXEC_NAME)
    add_executable(${PROJECT_NAME}_${EXEC_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${EXEC_NAME}.c)
endfunction()