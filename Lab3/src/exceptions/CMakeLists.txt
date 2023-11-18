cmake_minimum_required(VERSION 3.20)

SET(SOURCE_FILES BaseExceptions.hpp 
                 ConsoleArgExceptions.hpp 
                 FormatExceptions.hpp 
                 UncorrectConfig.hpp
                 ConsoleArgExceptions.cpp 
                 FormatExceptions.cpp
                 UncorrectConfig.cpp
                 )

add_library(exceptions STATIC ${SOURCE_FILES})

target_include_directories(exceptions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

