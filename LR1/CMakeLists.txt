cmake_minimum_required(VERSION 3.28)

project(LR1)

add_executable(Task_3 Task_3.cpp)
target_include_directories(Task_3 PRIVATE /usr/include/)
target_compile_options(Task_3 PRIVATE ${OPTIONS})
target_link_options(Task_3 PRIVATE ${OPTIONS})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  ctest
  test.cpp
)
target_link_libraries(
  ctest
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ctest)