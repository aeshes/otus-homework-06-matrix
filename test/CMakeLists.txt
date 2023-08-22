 cmake_minimum_required(VERSION 3.5)

 project(test)

 add_executable(test matrix_test.cpp)

 target_include_directories(test PRIVATE ../lib/include)

 target_link_libraries(test PRIVATE GTest::gtest_main)
