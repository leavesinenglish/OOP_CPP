cmake_minimum_required(VERSION 3.20)
project(merging_iterator)

set(CMAKE_CXX_STANDARD 23)
add_subdirectory(GoogleTest/googletest)
include_directories(GoogleTest/googletest/googletest/include)
add_executable(merging_iterator merging_iterator.hpp m_iter_exceptions.hpp tests.cpp)
target_link_libraries(merging_iterator gtest gtest_main) 
