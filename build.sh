#!/bin/bash

# Clone the project, find CMakeLists.txt and Create a build directory.
cmake -S . -B build
cd build
# Compile and Install the project
sudo make install
