cmake_minimum_required(VERSION 3.20)

file(GLOB SOURCE_FILES  
"${CMAKE_CURRENT_SOURCE_DIR}/converter/includes/*.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/converter/src/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/converter/src/*.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/file/includes/*.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/file/src/*.cpp"

)
add_library(model STATIC ${SOURCE_FILES})

target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)

target_link_libraries(model PUBLIC factory)
