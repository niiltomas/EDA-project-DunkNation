cmake_minimum_required(VERSION 3.24)
project(EDA2 C)

set(CMAKE_C_STANDARD 11)

add_library(EDA2 library.c estructuras.c code.c "codigo primcipal.c")
