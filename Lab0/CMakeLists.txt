cmake_minimum_required(VERSION 3.14)

project(Lab0)

set (CMAKE_CXX_STANDARD 20)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/includes/*.h"
		"${PROJECT_SOURCE_DIR}/includes/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
		"${PROJECT_SOURCE_DIR}/src/*.c"
        )

add_executable(Lab0 ${all_SRCS})

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

