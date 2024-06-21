#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Define build directory
BUILD_DIR="build"

# Function to check if a command exists
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Check if we are on a Debian-based system (for apt-get)
if command_exists apt-get; then
    echo "Updating package list and installing libgtest-dev..."
    sudo apt-get update
    sudo apt-get install -y libgtest-dev

    # Compile and install Google Test
    echo "Compiling and installing Google Test..."
    cd /usr/src/gtest
    sudo cmake .
    sudo make

    # Copy the libraries to /usr/lib
    sudo cp lib/*.a /usr/lib
    echo "Google Test libraries installed."

    # Return to the original directory
    cd - > /dev/null
fi

# Clean the build directory if it exists
if [ -d "$BUILD_DIR" ]; then
    echo "Removing existing build directory..."
    rm -rf "$BUILD_DIR"
fi

# Create a new build directory
echo "Creating build directory..."
mkdir "$BUILD_DIR"
cd "$BUILD_DIR"

# Generate Makefiles with CMake
echo "Running CMake..."
cmake ..

# Build the project
echo "Building the project..."
make

# Run unit tests
echo "Running unit tests..."
ctest

# Optionally, run the main program
echo "Running the main program..."
./main

# Script completed
echo "Done."
