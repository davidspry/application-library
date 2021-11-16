cmake_minimum_required(VERSION 3.20)
project(ApplicationLibrary)

set(CMAKE_CXX_STANDARD 20)

# Add tests
add_subdirectory(tests)

# Obtain the source files
file(GLOB_RECURSE AL_SOURCES source/*.cpp)
file(GLOB_RECURSE AL_HEADERS source/*.hpp)

# Include the source files
include_directories(source)