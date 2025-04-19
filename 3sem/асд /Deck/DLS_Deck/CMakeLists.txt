cmake_minimum_required(VERSION 3.23)
project(DLS_Deck C)

set(CMAKE_C_STANDARD 99)

add_executable(DLS_Deck main.c dlist.h deck.h)
