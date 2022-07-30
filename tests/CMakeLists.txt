cmake_minimum_required(VERSION 3.2)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)

set (SOURCES
    ../src/algorithm.cpp
    ../src/buttons.cpp
    ../src/interface.cpp
    ../src/pillar.cpp
    ../src/sorter.cpp
    ../src/raygui.cpp
    example_test.cpp
)

add_executable(${TEST_EXEC_NAME} ${SOURCES})
target_link_libraries(${TEST_EXEC_NAME} PUBLIC gtest_main ${PROJECT_LIBS})
set_target_properties(${TEST_EXEC_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "..")


add_test(
    NAME ${TEST_EXEC_NAME}
    COMMAND ${TEST_EXEC_NAME}
)
