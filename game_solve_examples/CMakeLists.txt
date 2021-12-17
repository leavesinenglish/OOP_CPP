cmake_minimum_required(VERSION 3.20)
project(game_solve_examples)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 99)
add_executable(game_solve_examples c_code.c game.cpp game.hpp task.cpp task.hpp arithmetic_operations.hpp operations.hpp operations.cpp arithmetic_operation_interface.hpp)
