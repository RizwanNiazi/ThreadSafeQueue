cmake_minimum_required(VERSION 3.10)

# Project name and version
project(ThreadSafeQueue VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable testing
enable_testing()

# Find GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add the Queue library (header-only)
add_library(Queue INTERFACE)
target_include_directories(Queue INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Add the test executable
add_executable(test_Queue test_Queue.cpp)
target_link_libraries(test_Queue PRIVATE GTest::GTest GTest::Main pthread)
target_link_libraries(test_Queue PRIVATE Queue)

# Add the main executable
add_executable(main main.cpp)
target_link_libraries(main PRIVATE Queue)

# Add a test for CTest to discover
add_test(NAME QueueTest COMMAND test_Queue)

