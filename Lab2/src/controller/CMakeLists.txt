cmake_minimum_required(VERSION 3.20)

file(GLOB SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        )

add_library(controller ${SOURCE_FILES})

target_include_directories(controller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(controller PUBLIC model view)