# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(ThreadSafeQueue VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Enable testing
enable_testing()

# Find GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add the test executable
add_executable(test_Queue test/test_Queue.cpp)

# Link the test executable against Google Test and pthread
target_link_libraries(test_Queue GTest::GTest GTest::Main pthread)

# Add the main executable
add_executable(main src/main.cpp)

# Add a test for CTest to discover
add_test(NAME QueueTest COMMAND test_Queue)

