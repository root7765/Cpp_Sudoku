cmake_minimum_required(VERSION 3.0.0)
project(sudoku_prj VERSION 0.1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror -pedantic")
FILE(GLOB Sources src/*.cpp)
add_executable(sudoku_ ${Sources})

#enable_testing()
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#add_executable( runUnitTests tests_sudoku.cpp src/Sudoku.cpp src/SudokuSolver.cpp)
#target_link_libraries(runUnitTests gtest gtest_main)
#add_test( runUnitTests runUnitTests )