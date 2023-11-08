cmake_minimum_required(VERSION 3.24)
project(TinyDNN)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(TinyDNN main.cpp src/core.cpp)
