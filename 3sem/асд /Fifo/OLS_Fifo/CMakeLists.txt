cmake_minimum_required(VERSION 3.23)
project(OLS_Fifo C)

set(CMAKE_C_STANDARD 99)

add_executable(OLS_Fifo main.c list.h fifo.h)
