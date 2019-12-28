cmake_minimum_required(VERSION 3.10)

project(queue_utils_test)

add_executable(queue_utils_test test.cpp queue_utils.cpp queue_utils.hpp)

target_link_libraries(queue_utils_test rt) #https://stackoverflow.com/questions/22316979/how-to-make-cmake-append-linker-flags-instead-of-prepending-them
