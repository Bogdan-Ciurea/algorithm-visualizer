#!/bin/bash

# This file is intended to autoformat the program before committing the code
clang-format -i src/*.cpp
clang-format -i include/*.h
clang-format -i include/standalone-functions/*.h