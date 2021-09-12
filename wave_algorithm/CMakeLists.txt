cmake_minimum_required(VERSION 3.20)
project(wave_algorithm)

set(CMAKE_CXX_STANDARD 23)

add_executable(wave_algorithm main.cpp maze_creator.cpp maze_creator.hpp output_wave_alg_solution.hpp output_wave_alg_solution.cpp wave_alg.hpp wave_alg.cpp work_with_file.hpp work_with_file.cpp)
