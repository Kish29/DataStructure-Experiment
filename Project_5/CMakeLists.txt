cmake_minimum_required(VERSION 3.16)

project(Project_5)

set(CMAKE_CXX_STANDARD 14)

set(INC_DIR include)

include_directories(${INC_DIR})

add_executable(Project_5 src/part1.cpp)