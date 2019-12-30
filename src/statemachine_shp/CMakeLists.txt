cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(statemachine_shp)

INCLUDE_DIRECTORIES(../database ../utilities)

set(sources main.cpp shpstatemachine.cpp shpstatemachine.h statemachine_constants.h)

add_executable(statemachine ${sources})
add_executable(simulated_sender simulated_sender.cpp)



find_package(cppzmq)
find_library(DATABASE_LIBRARY database_interface HINTS /home/soren/9sem/ESD/embeddedProject/src/database/build)
find_library(SHP_QUEUE_LIBRARY shp_queue HINTS /home/soren/9sem/ESD/embeddedProject/src/utilities/build)

target_link_libraries(statemachine rt cppzmq ${DATABASE_LIBRARY} ${SHP_QUEUE_LIBRARY})

target_link_libraries(simulated_sender rt cppzmq ${DATABASE_LIBRARY} ${SHP_QUEUE_LIBRARY})
