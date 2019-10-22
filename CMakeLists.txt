cmake_minimum_required(VERSION 2.8.7)
project(embeddedProj C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++0x")
#Set the sources of the project
set(project_sources
        main.cpp
        src/CardReader.cpp include/CardReader.h
        src/GPIO.cpp include/GPIO.h
        src/NumpadDriver.cpp include/NumpadDriver.h
        src/DisplayDriver.cpp include/DisplayDriver.h include/Core.h)

#Adds executable to the bin direcory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

#posix threads
find_package (Threads)

add_executable(embeddedProj ${project_sources})
#rt and thread library linkage
target_link_libraries (embeddedProj ${CMAKE_THREAD_LIBS_INIT} rt)
