cmake_minimum_required(VERSION 3.28)

project(LR5)

set(FILE_NAME "main.cpp")
set(SOURCES Task_3 Task_4 Task_5)

include_directories(include)
include_directories(src/LR5_StaticLib1)

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

enable_testing()
add_executable(tests test/gtest.cpp)
target_link_libraries(tests GTest::gtest_main LR5_StaticLib1)
target_link_directories(tests PUBLIC src/LR5_1/x64/Debug/)
gtest_discover_tests(tests)
add_custom_command(TARGET tests POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}\\src\\LR5_2\\x64\\Debug\\LR5_DynamicLib.dll ${PROJECT_BINARY_DIR}\\Debug)  

foreach(SOURCE ${SOURCES})
    add_executable(${SOURCE} src/${SOURCE}/${FILE_NAME})
    target_include_directories(${SOURCE} PRIVATE include)
endforeach(SOURCE ${SOURCES})
