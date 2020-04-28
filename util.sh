#!/bin/sh
# simple shell script to clean build
case "$1" in
    "")
        echo "Performing Clean Build"
        rm -rf build
        echo "Removed existing build directory"
        mkdir build
        cd build
        cmake ..
        make
        cd ..
        cp compile_commands.json ../
        exit 0
        ;;
    "run")
        echo "Running main"
        ./build/main
        exit 0
        ;;
    "make")
        cd build
        make
        cd ..
        echo "Build complete"
        exit 0
        ;;
    "clean")
        rm -rf build
        echo "Deleted build directory"
        exit 0
        ;;
    *)
        echo "Usage: sh buildscript.sh [run/make]"
        exit 1
        ;;
esac
