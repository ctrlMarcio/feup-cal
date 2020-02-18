cmake_minimum_required(VERSION 3.10)
project(CAL_FP01)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)



add_executable(CAL_FP01 main.cpp test/tests.cpp src/Change.cpp src/Factorial.cpp src/Partitioning.cpp src/Sum.cpp)

target_link_libraries(CAL_FP01 gtest gtest_main)
