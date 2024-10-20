cmake_minimum_required(VERSION 3.28)

project(LR4)

set(FILE_NAME_CPP "main.cpp")
set(FILE_NAME_C "main.c")
set(CPP_SOURCES Task_1 Task_2 Task_3)
set(C_SOURCES Task_4 Task_5 Task_6)

include_directories(include)

find_package(GTest REQUIRED)
enable_testing()
add_executable(gtest test/gtest.cpp)
target_link_libraries(gtest GTest::gtest_main)
gtest_discover_tests(gtest)

foreach(FOLDER_NAME ${CPP_SOURCES})
    add_executable(${FOLDER_NAME} src/${FOLDER_NAME}/${FILE_NAME_CPP})
endforeach(FOLDER_NAME ${CPP_SOURCES})

foreach(FOLDER_NAME ${C_SOURCES})
    add_executable(${FOLDER_NAME} src/${FOLDER_NAME}/${FILE_NAME_C})
endforeach(FOLDER_NAME ${C_SOURCES})