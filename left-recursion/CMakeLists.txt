cmake_minimum_required(VERSION 3.27)
project(left_recursion)

set(CMAKE_CXX_STANDARD 17)

add_executable(left_recursion main.cpp
        source/CFG.cpp
        include/CFG.h
        source/LeftRecursion.cpp
        include/LeftRecursion.h)
