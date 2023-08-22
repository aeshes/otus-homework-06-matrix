cmake_minimum_required(VERSION 3.5)

project(Matrix)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest)

add_subdirectory(lib)
add_subdirectory(test)
