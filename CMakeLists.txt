# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(ThreadSafeQueue)

set(CMAKE_CXX_STANDARD 14)

# Add the queue header and source files
add_library(Queue Queue.h)

# Enable testing and add Google Test
enable_testing()

# Add GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add the test executable
add_executable(test_Queue test_Queue.cpp)

# Link the test executable against the Queue library and Google Test
target_link_libraries(test_Queue Queue ${GTEST_LIBRARIES} pthread)

# Add a test for CTest to discover
add_test(NAME QueueTest COMMAND test_Queue)
