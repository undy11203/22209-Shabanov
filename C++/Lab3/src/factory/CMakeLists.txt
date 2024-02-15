cmake_minimum_required(VERSION 3.20)

file(GLOB SOURCE_FILES  
"${CMAKE_CURRENT_SOURCE_DIR}/includes/Factory/*.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
add_library(factory STATIC ${SOURCE_FILES})

target_include_directories(factory PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)
