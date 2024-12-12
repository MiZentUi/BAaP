cmake_minimum_required(VERSION 3.28)

project(LR6)

set(CMAKE_CXX_CPPCHECK "cppcheck")
set(CMAKE_CXX_CLANG_TIDY "clang-tidy" "-checks=some-check")
set(FILE_NAME_CPP "main.cpp")
set(CPP_SOURCES Task_1 Task_2 Task_3)
set(SANITIZER "address")

add_compile_options("-fsanitize=${SANITIZER}")
add_link_options("-fsanitize=${SANITIZER}")

include_directories(include)

find_package(GTest REQUIRED)
enable_testing()
add_executable(gtest test/gtest.cpp include/tools.cpp)
target_link_libraries(gtest GTest::gtest_main)
gtest_discover_tests(gtest)

foreach(FOLDER_NAME ${CPP_SOURCES})
    add_executable(${FOLDER_NAME} src/${FOLDER_NAME}/${FILE_NAME_CPP} include/tools.cpp)
endforeach(FOLDER_NAME ${CPP_SOURCES})