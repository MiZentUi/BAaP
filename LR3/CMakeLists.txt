cmake_minimum_required(VERSION 3.28)

project(LR3)

set(FILE_NAME "main.cpp")
set(SOURCES Task_1 Task_2 Task_3 Task_4 Task_5 Task_6 Task_7 Task_8)

foreach(TARGET_NAME ${SOURCES})
    add_executable(${TARGET_NAME} ${TARGET_NAME}/${FILE_NAME})
    target_compile_options(${TARGET_NAME} PRIVATE ${OPTIONS})
    target_link_options(${TARGET_NAME} PRIVATE ${OPTIONS})
endforeach(TARGET_NAME ${SOURCES})