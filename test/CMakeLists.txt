 cmake_minimum_required(VERSION 3.5)

 project(tests)

 add_executable(matrix matrix_test.cpp)

 target_include_directories(matrix PRIVATE ../lib/include)

 target_link_libraries(matrix PRIVATE GTest::gtest_main)
