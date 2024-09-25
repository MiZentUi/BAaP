cmake_minimum_required(VERSION 3.28)

project(LR2)

set(SOURCES Task_1.cpp Task_2.cpp Task_3.cpp Task_4.cpp Task_5.cpp Task_6.cpp Task_7.cpp Task_8.cpp Task_9.cpp Task_10.cpp Task_11.cpp Task_12.cpp Task_13.cpp)

foreach(FILE_NAME ${SOURCES})
    string(REPLACE ".cpp" "" TARGET_NAME ${FILE_NAME})
    add_executable(${TARGET_NAME} ${TARGET_NAME}/${FILE_NAME})
    target_compile_options(${TARGET_NAME} PRIVATE ${OPTIONS})
    target_link_options(${TARGET_NAME} PRIVATE ${OPTIONS})
endforeach(FILE_NAME ${SOURCES})