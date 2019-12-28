# embeddedProject

## Setup toolchain and remote debug
```
https://blog.jetbrains.com/clion/2018/09/initial-remote-dev-support-clion/?fbclid=IwAR1x0Y8wC8Lr7KHFZui8Xj9QEbFQ5DoBaKVO55o_0b6USQ-Yidcolhl4PQU#initial_remote_projects_support_what_s_that    
```

Build instructions
==================

Build steps:

1. Build [libzmq](https://github.com/zeromq/libzmq) via cmake. This does an out of source build and installs the build files
   - download and unzip the lib, cd to directory
   - mkdir build
   - cd build
   - cmake ..
   - sudo make -j4 install

2. Build [cppzmq](https://github.com/zeromq/cppzmq) via cmake. This does an out of source build and installs the build files
   - download and unzip the lib, cd to directory
   - mkdir build
   - cd build
   - cmake ..
   - sudo make -j4 install

Using this:

A cmake find package scripts is provided for you to easily include this library.
Add these lines in your CMakeLists.txt to include the headers and library files of
cpp zmq (which will also include libzmq for you).

```
#find cppzmq wrapper, installed by make of cppzmq
find_package(cppzmq)
target_link_libraries(*Your Project Name* cppzmq)
```