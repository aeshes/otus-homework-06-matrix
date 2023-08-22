 cmake_minimum_required(VERSION 3.5)

 project(lib)

 add_executable(matrix main.cpp)

 target_include_directories(matrix PRIVATE ./include)
