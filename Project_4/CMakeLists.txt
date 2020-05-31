cmake_minimum_required(VERSION 3.16)
project(Project_4)

set(CMAKE_CXX_STANDARD 14)

set(INC_DIR include)

include_directories(${INC_DIR})

add_executable(Project_4 MainTest.cpp src/tree.cpp src/suan_png.cpp src/pxl.cpp)