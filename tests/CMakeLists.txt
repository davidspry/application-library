cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(TESTS_HANDLE ${PROJECT_NAME}Tests)

# Require and locate GoogleTest
find_package(GTest REQUIRED)

# Include the library sources in the header search path
include_directories(../source/)

# Create the testing executable
add_executable(${TESTS_HANDLE} TestMain.cpp TestPoint.hpp TestBounds.hpp)

# Link with GoogleTest
target_link_libraries(${TESTS_HANDLE} GTest::gtest)