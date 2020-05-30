cmake_minimum_required(VERSION 3.16)
project(Project_1)

set(CMAKE_CXX_STANDARD 14)

set(INC_DIR include)
set(SRC_DIR src)

include_directories(${INC_DIR})

add_executable(Project_1 ${INC_DIR} src/workflow.cpp src/worker.cpp src/vector.cpp main.cpp)