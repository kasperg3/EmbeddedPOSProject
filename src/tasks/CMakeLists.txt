cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(CustomerDisplayTask_zmq)

find_package(cppzmq)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../peripherals)

set(source_files CustomerDisplayTask_zmq.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../peripherals/CustomerDisplay.cpp)

add_executable(cd_task ${source_files})

target_link_libraries(cd_task cppzmq)