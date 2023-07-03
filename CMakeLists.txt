# Thanks a lot to these github contributors
# https://github.com/ttroy50/cmake-examples
# https://github.com/ArchieAtkinson/CppTemplate/tree/main/Raylib


# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.11.3)

# Set a default C++ compile flag
project(visualizer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add the headers in the /include directory
include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

# -------------------
# Download submodules and check if they exist

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
  # Update submodules as needed
  option(GIT_SUBMODULE "Check submodules during build" ON)
  if(GIT_SUBMODULE)
    message(STATUS "Submodule update")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
      message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    endif()
  endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/modules/googletest/CMakeLists.txt" OR 
  NOT EXISTS "${PROJECT_SOURCE_DIR}/modules/raylib/CMakeLists.txt")
  message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

# -------------------

# -------------------
# Libraries
# Add Google Tests
add_subdirectory(modules/googletest)
include_directories({PROJECT_NAME} PUBLIC modules/googletest/googletest/include)
link_libraries(gtest_main)

# Add Raylib
add_subdirectory(modules/raylib)
include_directories(${PROJECT_NAME} PRIVATE modules/raylib/src)
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

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    set(TEST_EXEC_NAME unit_tests)
    add_subdirectory(tests)
endif()
# -------------------