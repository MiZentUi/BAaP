cmake_minimum_required(VERSION 3.28)

project(LR7)

set(CMAKE_CXX_CPPCHECK "cppcheck")
set(CMAKE_CXX_CLANG_TIDY 
	"clang-tidy" 
	"-checks= \
		bugprone-*, \
		cppcoreguidelines-*, \
		modernize-*, \
		readability-*, \
		-modernize-use-trailing-return-type, \
		-cppcoreguidelines-pro-bounds-pointer-arithmetic, \
		-cppcoreguidelines-owning-memory, \
		-readability-braces-around-statements, \
		-readability-suspicious-call-argument, \
		-readability-magic-numbers, \
		-cppcoreguidelines-avoid-magic-numbers, \
		-cppcoreguidelines-avoid-c-arrays, \
		-bugprone-easily-swappable-parameters, \
		-modernize-avoid-c-arrays, \
		-cppcoreguidelines-pro-bounds-constant-array-index, \
		-clang-analyzer-core.uninitialized.Assign, \
		-readability-function-cognitive-complexity \
")
set(FILE_NAME_CPP "main.cpp")
set(CPP_SOURCES Task_1 Task_2 Task_3 Task_4 Task_5)
set(SANITIZER "address")

add_compile_options("-fsanitize=${SANITIZER}")
add_link_options("-fsanitize=${SANITIZER}")

include_directories(include)
add_library(tools include/tools.cpp)

foreach(FOLDER_NAME ${CPP_SOURCES})
	add_executable(${FOLDER_NAME} src/${FOLDER_NAME}/${FILE_NAME_CPP})
	target_link_libraries(${FOLDER_NAME} tools)
endforeach(FOLDER_NAME ${CPP_SOURCES})