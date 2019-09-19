cmake_minimum_required(VERSION 2.8.7)
project(embeddedProj)

set(CMAKE_CXX_STANDARD 11)

set( project_sources main.cpp source/CardReader.cpp)

add_executable(embeddedProj ${project_sources})