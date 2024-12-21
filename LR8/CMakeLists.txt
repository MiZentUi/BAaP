cmake_minimum_required(VERSION 3.28)

project(LR7)

set(FILE_NAME_CPP "main.cpp")
set(CMAKE_SOURCE_DIR src)

include_directories(include)

add_library(train_tools ${CMAKE_SOURCE_DIR}/train_tools.cpp)
add_library(student_tools ${CMAKE_SOURCE_DIR}/student_tools.cpp)

add_executable(Task_1 ${CMAKE_SOURCE_DIR}/Task_1/${FILE_NAME_CPP})
target_link_libraries(Task_1 train_tools)

add_executable(Task_2 ${CMAKE_SOURCE_DIR}/Task_2/${FILE_NAME_CPP})
target_link_libraries(Task_2 student_tools)