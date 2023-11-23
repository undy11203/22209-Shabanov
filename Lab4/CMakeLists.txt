cmake_minimum_required(VERSION 3.20)

project(Templete)


SET(SOURCE_FILES main.cpp
                 CSVParser.tpp
                 execptions/BaseExecption.hpp
                 execptions/DataExecption.hpp
                 )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")