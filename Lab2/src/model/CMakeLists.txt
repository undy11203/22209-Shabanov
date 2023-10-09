cmake_minimum_required(VERSION 3.20)

file(GLOB SOURCE_FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/game_logic/includes/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/game_logic/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/game_logic/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/game_logic/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/file/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/file/*.cpp"
        )

add_library(model ${SOURCE_FILES})

target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})