cmake_minimum_required(VERSION 3.16)
project(Project_4)

set(CMAKE_CXX_STANDARD 14)

set(INC_DIR include/)

include_directories(${INC_DIR})

add_executable(Project_4 src/test.cpp src/tree.cpp src/pxl.cpp)# src/test.cpp)