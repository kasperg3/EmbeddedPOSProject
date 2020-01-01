cmake_minimum_required(VERSION 3.10)
project(shp_database)

find_package(cppzmq)

set (source_files
    db_interface_constants.hpp
    db_interface.cpp
    db_interface.hpp
    item.cpp
    item.hpp
    receipt.cpp
    receipt.hpp
    simple_item.cpp
    simple_item.hpp
)



add_library(database_interface STATIC ${source_files})

add_executable(db_interface_test main.cpp ${source_files})
target_link_libraries(db_interface_test cppzmq database_interface)


#add_library(database_interface STATIC ${source_files})

