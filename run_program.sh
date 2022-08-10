#!/bin/bash

# This file is inteded to build and run the program with grater ease
mkdir build
cmake -S . -B build/
make -C build/
./build/visualizer