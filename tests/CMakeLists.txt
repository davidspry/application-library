cmake_minimum_required(VERSION 3.20)
project(ApplicationLibrary-Tests)

set(CMAKE_CXX_STANDARD 20)

# Obtain the tests
file(GLOB TESTS Test*.hpp)

# Obtain the UI sources
file(GLOB UI_SOURCES ../source/UI/*.hpp)

# Include the sources
include_directories(../source/)

# Create the testing executable
add_executable(${PROJECT_NAME} ${TESTS} ${UI_SOURCES} TestMain.cpp)

# Link with GoogleTest
find_package(GTest REQUIRED)
target_link_libraries(${PROJECT_NAME} GTest::gtest)