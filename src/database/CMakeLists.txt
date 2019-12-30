cmake_minimum_required(VERSION 3.10)
project(shp_database)

find_package(cppzmq)

set (srcFiles
    db_interface_constants.hpp
    db_interface.cpp
    db_interface.hpp
    item.cpp
    item.hpp
    shp_database_main_example.cpp
    receipt.cpp
    receipt.hpp
    simple_item.cpp
    simple_item.hpp
)

add_executable(db_interface_test ${srcFiles})
target_link_libraries(db_interface_test cppzmq)


add_library(database_interface
    STATIC
    db_interface_constants.hpp
    db_interface.cpp
    db_interface.hpp
    item.cpp
    item.hpp
    receipt.cpp
    receipt.hpp
    simple_item.cpp
    simple_item.hpp)

