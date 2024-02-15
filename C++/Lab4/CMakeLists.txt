cmake_minimum_required(VERSION 3.20)

project(Templete)

set (CMAKE_CXX_STANDARD 20)

SET(SOURCE_FILES main.cpp
                 CSVParser.tpp
                 TupleOutput.hpp
                 exceptions/DataExecption.hpp
                 )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")