cmake_minimum_required(VERSION 3.10.0)
project(SFML_Test VERSION 0.1.0 LANGUAGES C CXX)

#C Language Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

# Path variables
set(SFML_INCLUDE_DIR "SFML_INCLUDE_PATH")
set(SFML_LIB_DIR "SFML_LIBRARIES_PATH")
set(SFML_BIN_DIR "SFML_BINARIES_PATH")

#Include + Lib
include_directories(
    ${SFML_INCLUDE_DIR}
    "${CMAKE_SOURCE_DIR}/include")
    
link_directories(
    ${SFML_LIB_DIR})

#Include .cpp files in directory (me thinks there is a better way to do this)
file(GLOB SOURCES 
"${CMAKE_SOURCE_DIR}/*.cpp"
"${CMAKE_SOURCE_DIR}/src/*.cpp"
"${CMAKE_SOURCE_DIR}/src/engine/*.cpp"
"${CMAKE_SOURCE_DIR}/src/game/scenes/*.cpp"
"${CMAKE_SOURCE_DIR}/src/game/components/*.cpp")

#Executable
add_executable(SFML_Test ${SOURCES})

# Link libraries based on build type
target_link_libraries(SFML_Test
    debug sfml-graphics-d sfml-window-d sfml-system-d
    optimized sfml-graphics sfml-window sfml-system
)

#Post
include(CTest)
enable_testing()

#Copy SFML DLLs to build directory
add_custom_command(TARGET SFML_Test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${SFML_BIN_DIR}/sfml-system$<$<CONFIG:Debug>:-d>-3.dll
    ${SFML_BIN_DIR}/sfml-window$<$<CONFIG:Debug>:-d>-3.dll
    ${SFML_BIN_DIR}/sfml-graphics$<$<CONFIG:Debug>:-d>-3.dll
    $<TARGET_FILE_DIR:SFML_Test>
    COMMAND_EXPAND_LISTS
)