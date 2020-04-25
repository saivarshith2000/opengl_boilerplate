#!/bin/sh

# simple shell script to clean build
rm -rf build
echo "Removed existing build directory"
mkdir build
cd build
cmake ..
make
