cmake_minimum_required(VERSION 3.14)
project(ApplicationLibrary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)

add_subdirectory(tests)

file(GLOB_RECURSE SOURCES source/*.cpp)
file(GLOB_RECURSE HEADERS source/*.hpp)

# Make the source files available in the parent scope
if(NOT ${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    set(APPLICATION_LIBRARY_SOURCES ${SOURCES} PARENT_SCOPE)
    set(APPLICATION_LIBRARY_HEADERS ${HEADERS} PARENT_SCOPE)
endif()