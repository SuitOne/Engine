cmake_minimum_required(VERSION 3.10.0)
project(Engine VERSION 0.1.0 LANGUAGES C CXX)
 
#C Language Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)
 
# Path variables
set(INCLUDE_DIR "X")
set(LIB_DIR "X")
set(BIN_DIR "X")
 
#Include + Lib
include_directories(
    ${INCLUDE_DIR}
    "${CMAKE_SOURCE_DIR}/include")
   
link_directories(
    ${LIB_DIR})
 
#Include .cpp files in directory
file(GLOB_RECURSE SOURCES
"${CMAKE_SOURCE_DIR}/src/*.cpp")
 
#Executable
add_executable(Engine ${SOURCES})
 
# Link libraries based on build type
target_link_libraries(Engine
    debug sfml-graphics-d sfml-window-d sfml-system-d
    optimized sfml-graphics sfml-window sfml-system
)
 
#Post
include(CTest)
enable_testing()
 
#Copy SFML DLLs to build directory
add_custom_command(TARGET Engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${BIN_DIR}/sfml-system$<$<CONFIG:Debug>:-d>-3.dll
    ${BIN_DIR}/sfml-window$<$<CONFIG:Debug>:-d>-3.dll
    ${BIN_DIR}/sfml-graphics$<$<CONFIG:Debug>:-d>-3.dll
    ${CMAKE_SOURCE_DIR}/resources/arial.ttf
    $<TARGET_FILE_DIR:Engine>
    COMMAND_EXPAND_LISTS
)
