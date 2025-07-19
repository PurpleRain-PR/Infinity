cmake_minimum_required(VERSION 3.31)
project(Infinity C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "-O3")

add_library(Infinity STATIC infinity.c
        initial.h)

