cmake_minimum_required(VERSION 3.20)

file(GLOB SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        )

add_library(view ${SOURCE_FILES})

target_include_directories(view PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
