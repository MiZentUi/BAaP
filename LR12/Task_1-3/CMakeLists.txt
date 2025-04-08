cmake_minimum_required(VERSION 3.28)

project(Task_1-3)

include_directories(include)

set(SOURCE_DIR src)
set(TEST_DIR tests)
set(MAIN_FILE_NAME main.cpp)
set(SOURCES)
set(TEST_SOURCES
    ${TEST_DIR}/gtest.cpp
)
set(TASKS
    Task_1
    Task_2
    Task_3
)

find_package(GTest REQUIRED)
enable_testing()
add_executable(gtest ${TEST_SOURCES})
target_link_libraries(gtest GTest::gtest_main)
gtest_discover_tests(gtest)

foreach(TASK ${TASKS})
    add_executable(${TASK} ${SOURCE_DIR}/${TASK}/${MAIN_FILE_NAME} ${SOURCES})
endforeach(TASK ${TASKS})