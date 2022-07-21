# Thanks a lot to these github contributors
# https://github.com/ttroy50/cmake-examples
# https://github.com/ArchieAtkinson/CppTemplate/tree/main/Raylib


# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.16.3)

# Set a default C++ compile flag
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)

# Set the project name
project(visualizer)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES 
    src/main.cpp
    src/algorithm.cpp
    src/buttons.cpp
    src/interface.cpp
    src/pillar.cpp
    src/sorter.cpp
    src/raygui.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})


# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Copy the assets
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Libraries
include(FetchContent)
FetchContent_Declare(raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 4.0.0
)
FetchContent_MakeAvailable(raylib)

target_include_directories(${PROJECT_NAME} PRIVATE ${raylib_SOURCE_DIR}/src/extras)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)