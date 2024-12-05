cmake_minimum_required(VERSION 3.25)
project(DFS C)

set(CMAKE_C_STANDARD 23)

add_executable(DFS main.c DFS.h DFS.c random.h random.c)
