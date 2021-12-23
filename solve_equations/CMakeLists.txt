cmake_minimum_required(VERSION 3.20)
project(solve_equations)

set(CMAKE_CXX_STANDARD 23)
add_subdirectory(Google_Tests/googletest)
include_directories(Google_Tests/googletest/googletest/include)
add_executable(solve_equations newtons_method.cpp newtons_method.hpp chord_method.cpp chord_method.hpp solution.cpp solution.hpp tests.cpp)
target_link_libraries(solve_equations gtest gtest_main)