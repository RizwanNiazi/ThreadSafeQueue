# Thread-Safe Queue Example

This project demonstrates a thread-safe queue implementation in C++ using mutexes and condition variables.

## Directory Structure

- `include/Queue.h`: Header file containing the `Queue` template class declaration.
- `include/Queue.hpp`: Implementation file containing definitions of `Queue` member functions.
- `src/main.cpp`: Example usage of `Queue` in a multithreaded environment.
- `tests/test_Queue.cpp`: GoogleTest unit tests for `Queue` functionalities.
- `CMakeLists.txt`: CMake configuration file for building the project.
- `run.sh`: Script to automate the build and test process.
- `LICENSE`: License file (MIT License).

## Features

- **Thread-Safe Operations**: Uses mutexes and condition variables to ensure safe multi-threaded access.
- **Blocking and Timeout Pop**: Provides methods to block indefinitely or throw an exception after a timeout if the queue is empty.
- **Overflow Handling**: Drops the oldest element when the queue is full and a new element is pushed.
- **Template Class**: Supports different data types through a template design.
- **Unit Testing**: Comprehensive unit tests using GoogleTest.

## Build Instructions

### Prerequisites

- **CMake**: Minimum version 3.10.
- **G++**: A C++ compiler.
- **Git**: For cloning the repository.

### Automated Build and Run

For a streamlined setup, you can use the provided `run.sh` script. This script automates the process of installing dependencies, building the project, and running tests.

Follow these steps:

1. Clone `ThreadSafeQueue` directory:
   ```bash
   git clone https://github.com/RizwanNiazi/ThreadSafeQueue.git
   cd ThreadSafeQueue

2. Remove existing build and then create build directory:
   ```bash
   chmod +x run.sh
   ./run.sh

## Usage

Modify `main.cpp` or add your own code to use the `Queue` class. Ensure proper synchronization in multithreaded environments.

## Author

Rizwan Nawaz

## License

This project is licensed under the MIT License - see the LICENSE file for details.

