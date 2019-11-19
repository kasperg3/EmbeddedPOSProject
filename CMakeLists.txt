cmake_minimum_required(VERSION 2.8.7)
project(embeddedProj C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++0x")
#Set the sources of the project
set(project_sources
        main.cpp
        src/peripherals/GPIO.cpp src/peripherals/GPIO.hpp
        src/peripherals/CardReader.cpp src/peripherals/CardReader.hpp
        src/peripherals/NumpadDriver.cpp src/peripherals/NumpadDriver.hpp
        src/peripherals/DisplayDriver.cpp src/peripherals/DisplayDriver.hpp
        src/peripherals/PushButton.cpp src/peripherals/PushButton.hpp
        src/peripherals/Timer.cpp src/peripherals/Timer.hpp

        src/tasks/NumpadDriverTask.cpp src/tasks/NumpadDriverTask.hpp
        src/tasks/DisplayDriverTask.cpp src/tasks/DisplayDriverTask.hpp

        src/event_handling/EventHandler.cpp src/event_handling/EventHandler.hpp
        src/event_handling/EventQueue.cpp src/event_handling/EventQueue.hpp
        src/state_handling/BombStateMachine.cpp src/state_handling/BombStateMachine.hpp
        src/Core.h
        )

#Adds executable to the bin direcory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

#posix threads
find_package (Threads)

add_executable(embeddedProj ${project_sources})
#rt and thread library linkage
target_link_libraries (embeddedProj ${CMAKE_THREAD_LIBS_INIT} rt)
