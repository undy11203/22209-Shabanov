cmake_minimum_required(VERSION 3.20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        )
add_library(controller STATIC ${SOURCE_FILES})

target_link_libraries(controller PUBLIC model view)