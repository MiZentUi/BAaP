cmake_minimum_required(VERSION 4.0)

project("Task 2")

set(INCLUDE_DIR include)
set(SOURCES 
    ${INCLUDE_DIR}/vector.h
    ${INCLUDE_DIR}/vectorheap.h
    ${INCLUDE_DIR}/list.h
    ${INCLUDE_DIR}/listheap.h
)

include_directories(${INCLUDE_DIR})

find_package(GTest REQUIRED)
enable_testing()
add_executable(gtest tests/gtest.cpp ${SOURCES})
target_link_libraries(gtest GTest::gtest_main)
gtest_discover_tests(gtest)