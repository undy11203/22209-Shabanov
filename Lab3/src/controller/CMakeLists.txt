cmake_minimum_required(VERSION 3.20)

SET(SOURCE_FILES SoundController.hpp SoundController.cpp)
add_library(controller STATIC ${SOURCE_FILES})

target_include_directories(controller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(controller PUBLIC model)