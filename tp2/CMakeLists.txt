cmake_minimum_required(VERSION 3.10)
project(CAL_FP02)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)



add_executable(CAL_FP02 main.cpp test/tests.cpp src/Labirinth.cpp src/Sudoku.cpp)

target_link_libraries(CAL_FP02 gtest gtest_main)
