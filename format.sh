#!/bin/bash

# This file is intended to autoformat the program before committing the code
clang-format -i include/*.h*
clang-format -i include/interfaces/*.h*
clang-format -i include/standalone-functions/*.h*

clang-format -i src/*.cpp
clang-format -i src/interfaces/*.cpp
clang-format -i src/standalone-functions/*.cpp

clang-format -i tests/*.cpp