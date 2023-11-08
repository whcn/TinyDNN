cmake_minimum_required(VERSION 3.24)
project(TinyDNN)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_PATH include lib/gtest/include)
set(LIB_PATH lib/gtest/lib)

set(SRC_FILES main.cpp src/core.cpp)
set(TEST_FILES test/test_basic_operation.cpp)
set(LIB_FILES gtest)

include_directories(${HEADER_PATH})

link_directories(${LIB_PATH})

add_executable(TinyDNN ${SRC_FILES} ${TEST_FILES})

target_link_libraries(TinyDNN PUBLIC ${LIB_FILES})
