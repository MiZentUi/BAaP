cmake_minimum_required(VERSION 4.0)

project("Task 1")

set(INCLUDE_DIR include)
set(SOURCES 
    ${INCLUDE_DIR}/bst.h
)

include_directories(${INCLUDE_DIR})

find_package(GTest REQUIRED)
enable_testing()
add_executable(gtest tests/gtest.cpp ${SOURCES})
target_link_libraries(gtest GTest::gtest_main)
gtest_discover_tests(gtest)