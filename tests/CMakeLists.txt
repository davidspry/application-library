cmake_minimum_required(VERSION 3.14)

Include(FetchContent)
set(CMAKE_CXX_STANDARD 20)
set(TESTS_HANDLE ${PROJECT_NAME}Tests)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)

# Include the library sources in the header search path
include_directories(../source/)

# Create the testing executable
add_executable(${TESTS_HANDLE} TestMain.cpp TestPoint.hpp TestBounds.hpp)

# Link with GoogleTest
target_link_libraries(${TESTS_HANDLE} GTest::gtest)