cmake_minimum_required(VERSION 3.26)
project(Lab5b)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab5b
        main.cpp
        queue.h
        circ_arr.h)
