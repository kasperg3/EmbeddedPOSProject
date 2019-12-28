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
        src/peripherals/InputEventDriver.cpp src/peripherals/InputEventDriver.h

        src/tasks/NumpadDriverTask.cpp src/tasks/NumpadDriverTask.hpp
        src/tasks/DisplayDriverTask.cpp src/tasks/DisplayDriverTask.hpp
        src/tasks/CardReaderTask.cpp src/tasks/CardReaderTask.hpp
        src/tasks/BarcodeScannerTask.cpp src/tasks/BarcodeScannerTask.hpp

        src/event_handling/EventHandler.cpp src/event_handling/EventHandler.hpp
        src/event_handling/EventQueue.cpp src/event_handling/EventQueue.hpp
        src/state_handling/BombStateMachine.cpp src/state_handling/BombStateMachine.hpp
        src/Core.h
        src/tasks/KeyboardTask.cpp src/tasks/KeyboardTask.h

        src/database/db_interface.cpp src/database/db_interface.hpp
        src/database/db_interface_constants.hpp
        src/database/item.cpp src/database/item.hpp
        src/database/receipt.cpp src/database/receipt.hpp
        src/database/simple_item.cpp src/database/simple_item.hpp
        )

#Adds executable to the bin direcory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

#posix threads
find_package (Threads)


#database dependency
find_package(cppzmq)

add_executable(embeddedProj ${project_sources})
#rt and thread library linkage
target_link_libraries (embeddedProj ${CMAKE_THREAD_LIBS_INIT} cppzmq rt)

