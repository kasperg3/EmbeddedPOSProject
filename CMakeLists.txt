cmake_minimum_required(VERSION 2.8.7)
project(embeddedProj)

set(CMAKE_CXX_STANDARD 11)

#Set the sources of the project
set(project_sources
        main.cpp
        src/CardReader.cpp)

#Adds executable to the bin direcory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable(embeddedProj ${project_sources})

#Tell cmake that x library is needed to compile
#target_link_libraries(embeddedProj PUBLIC x)