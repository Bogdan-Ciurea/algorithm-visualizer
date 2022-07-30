# Thanks a lot to these github contributors
# https://github.com/ttroy50/cmake-examples
# https://github.com/ArchieAtkinson/CppTemplate/tree/main/Raylib


# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.2)

# Set a default C++ compile flag
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)
set (CMAKE_C_STANDARD 99)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_POSITION_INDEPENDENT_CODE ON)

# Set the project name
project(visualizer)

# Add the headers in the /include directory
include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

# -------------------
# Libraries
# Add Raylib
include(FetchContent)
FetchContent_Declare(raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 4.0.0
)
FetchContent_MakeAvailable(raylib)

# Add Google Tests
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(${PROJECT_NAME} PRIVATE ${raylib_SOURCE_DIR}/src/extras)
link_libraries(raylib)
# -------------------

# -------------------
# Add the main project
set(PROJECT_LIBS project_libs)

# Copy the assets
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(src)
# -------------------

# -------------------
# Add testing

enable_testing()
set(TEST_EXEC_NAME unit_tests)
add_subdirectory(tests)

# -------------------