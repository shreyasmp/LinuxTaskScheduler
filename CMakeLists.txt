cmake_minimum_required(VERSION 3.19)
project(LinuxTaskScheduler)

set(CMAKE_CXX_STANDARD 14)

add_executable(LinuxTaskScheduler src/headers/RBTree.h src/Tree.cpp src/TaskScheduler.cpp src/InputParse.cpp src/main.cpp)