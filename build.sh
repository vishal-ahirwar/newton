#!/bin/bash

# Create a build directory (if it doesn't exist) and navigate to it
mkdir -p build
cd build

# Run CMake to configure the project
cmake ..

# Compile the project using make (you can adjust the number of CPU cores with -j)
make -j$(nproc)
