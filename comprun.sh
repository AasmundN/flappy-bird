#!/bin/bash

# exit script at first error
set -u -e

echo "Compiling program..."
echo

# run makefile
make

echo
echo "Compilation finished!"
echo "Running program..."
echo

# run the program
./build/main
