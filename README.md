# Thread-Safe Queue Example

This project demonstrates a thread-safe queue implementation in C++ using mutexes and condition variables.

## Structure

- `Queue.h`: Header file containing the `Queue` template class declaration.
- `Queue.hpp`: Implementation file containing definitions of `Queue` member functions.
- `test_Queue.cpp`: GoogleTest unit tests for `Queue` functionalities.
- `main.cpp`: Example usage of `Queue` in a multithreaded environment.

## Build Instructions

1. Ensure you have CMake installed (minimum version 3.10).
2. Ensure you have git and g++ installed.
3. Clone this repository.
4. Navigate to the cloned directory and create a build directory.
5. Inside the build directory, run `cmake ..` followed by `make` to build the executables.
6. Run `./test_Queue` to execute unit tests.
7. Run `./main` to execute the main program example.

## Usage

Modify `main.cpp` or add your own code to use the `Queue` class. Ensure proper synchronization in multithreaded environments.

## Author

Rizwan Nawaz

## License

This project is licensed under the MIT License - see the LICENSE file for details.

