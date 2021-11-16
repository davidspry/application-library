cmake_minimum_required(VERSION 3.20)
project(ApplicationLibrary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# Add tests
add_subdirectory(tests)

# Obtain the source files
file(GLOB_RECURSE SOURCES source/*.cpp)
file(GLOB_RECURSE HEADERS source/*.hpp)

# Make the source files available in the parent scope
set(APPLICATION_LIBRARY_SOURCES ${SOURCES} PARENT_SCOPE)
set(APPLICATION_LIBRARY_HEADERS ${HEADERS} PARENT_SCOPE)