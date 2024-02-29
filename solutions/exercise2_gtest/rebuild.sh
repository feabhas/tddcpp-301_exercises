#!/bin/bash

rm -rf build    # Remove the build directory
cmake -S . -B build  # Create the build directory and run cmake
cmake --build build # Build the project
cmake --build build --target test # Run the tests
