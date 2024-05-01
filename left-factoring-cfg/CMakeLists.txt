cmake_minimum_required(VERSION 3.27)
project(left_factoring_cfg)

set(CMAKE_CXX_STANDARD 17)

add_executable(left_factoring_cfg main.cpp
        source/LeftFactorer.cpp
        include/LeftFactorer.h
        source/CFG.cpp
        include/CFG.h)
