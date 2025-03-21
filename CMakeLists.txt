cmake_minimum_required(VERSION 3.10)
project(SFML_Test VERSION 0.1.0 LANGUAGES C CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Attempt to find SFML if it's installed system-wide
option(USE_SYSTEM_SFML "Use system-installed SFML via find_package" ON)

if(USE_SYSTEM_SFML)
    find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
    message(STATUS "Using system-installed SFML")
else()
    # Let user provide paths manually via presets or command line
    set(SFML_INCLUDE_DIR "" CACHE PATH "Path to SFML includes")
    set(SFML_LIB_DIR "" CACHE PATH "Path to SFML libraries")
    set(SFML_BIN_DIR "" CACHE PATH "Path to SFML DLLs")

    if(NOT SFML_INCLUDE_DIR OR NOT SFML_LIB_DIR)
        message(FATAL_ERROR "SFML paths not set and system SFML not used. Set SFML_INCLUDE_DIR and SFML_LIB_DIR or enable USE_SYSTEM_SFML.")
    endif()

    include_directories(${SFML_INCLUDE_DIR})
    link_directories(${SFML_LIB_DIR})
endif()

# Add your includes
include_directories(${CMAKE_SOURCE_DIR}/include)

# Automatically grab all .cpp files recursively
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Create executable
add_executable(SFML_Test ${SOURCES})

# Link SFML libs
if(USE_SYSTEM_SFML)
    target_link_libraries(SFML_Test sfml-graphics sfml-window sfml-system)
else()
    target_link_libraries(SFML_Test
        debug sfml-graphics-d sfml-window-d sfml-system-d
        optimized sfml-graphics sfml-window sfml-system
    )
endif()

# Post build: Copy DLLs (Windows only, optional)
if(WIN32 AND SFML_BIN_DIR)
    add_custom_command(TARGET SFML_Test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SFML_BIN_DIR}/sfml-system$<$<CONFIG:Debug>:-d>-3.dll
            ${SFML_BIN_DIR}/sfml-window$<$<CONFIG:Debug>:-d>-3.dll
            ${SFML_BIN_DIR}/sfml-graphics$<$<CONFIG:Debug>:-d>-3.dll
            $<TARGET_FILE_DIR:SFML_Test>
        COMMAND_EXPAND_LISTS
    )
endif()

# Optional testing support
include(CTest)
enable_testing()
