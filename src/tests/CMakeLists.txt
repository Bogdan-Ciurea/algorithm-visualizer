cmake_minimum_required(VERSION 3.16.3)

set (This unit_tests)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)

set (Sources
    example_test.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
)

target_link_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_test(
    NAME ${This}
    COMMAND ${This}
)