cmake_minimum_required(VERSION 3.20)

project(Lab1)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_subdirectory(src/CircleBuffer)
include_directories(src/)

add_subdirectory(googletest)
add_subdirectory(tests)
