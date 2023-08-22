 cmake_minimum_required(VERSION 3.5)

 project(tests)

 add_executable(tests matrix_test.cpp)

 target_include_directories(tests PRIVATE ../lib/include)

 target_link_libraries(tests PRIVATE GTest::gtest_main)
