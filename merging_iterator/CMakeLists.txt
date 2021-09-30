cmake_minimum_required(VERSION 3.20)
project(merging_iterator)

set(CMAKE_CXX_STANDARD 23)

add_executable(merging_iterator main.cpp merging_iterator.hpp m_iter_exceptions.hpp)
