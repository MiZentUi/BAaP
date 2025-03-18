cmake_minimum_required(VERSION 3.28)

project("Task 3-4")

set(CMAKE_CXX_CLANG_TIDY 
	"clang-tidy" 
	"-checks= \
		bugprone-*, \
		cppcoreguidelines-*, \
		modernize-*, \
		readability-*, \
		-modernize-use-trailing-return-type, \
		-cppcoreguidelines-avoid-magic-numbers, \
		-readability-magic-numbers, \
		-cppcoreguidelines-owning-memory, \
		-cppcoreguidelines-pro-type-cstyle-cast, \
")

set(SOURCE_DIR src)
set(SOURCES 
    ${SOURCE_DIR}/number.cpp 
    ${SOURCE_DIR}/binaryoperation.cpp 
    ${SOURCE_DIR}/tools.cpp
)

include_directories(include)

find_package(GTest REQUIRED)
enable_testing()
add_executable(gtest test/gtest.cpp ${SOURCES})
target_link_libraries(gtest GTest::gtest_main)
gtest_discover_tests(gtest)