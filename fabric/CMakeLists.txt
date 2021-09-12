cmake_minimum_required(VERSION 3.20)
project(fabric C)

set(CMAKE_C_STANDARD 11)

add_executable(fabric main.c new.h new.c point.c point.h line.c line.h circle.c circle.h rect.c rect.h fabric.c fabric.h)

