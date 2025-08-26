cmake_minimum_required(VERSION 3.15)

project(nacbot C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(nacbot src/main.c)