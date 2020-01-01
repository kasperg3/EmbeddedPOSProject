cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(statemachine_shp)

INCLUDE_DIRECTORIES(../database ../utilities)

set(source_files main.cpp shpstatemachine.cpp shpstatemachine.h statemachine_constants.h)

add_executable(statemachine ${source_files})
add_executable(simulated_sender simulated_sender.cpp)

find_package(cppzmq)
find_library(DATABASE_LIBRARY database_interface HINTS ${CMAKE_CURRENT_SOURCE_DIR}/../database/build)
find_library(SHP_QUEUE_LIBRARY shp_queue HINTS ${CMAKE_CURRENT_SOURCE_DIR}/../utilities/build)

target_link_libraries(statemachine rt cppzmq ${DATABASE_LIBRARY} ${SHP_QUEUE_LIBRARY})

target_link_libraries(simulated_sender rt cppzmq ${DATABASE_LIBRARY} ${SHP_QUEUE_LIBRARY})
