cmake_minimum_required(VERSION 3.20)

set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(config INTERFACE)

target_include_directories(config INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
