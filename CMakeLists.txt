cmake_minimum_required(VERSION 3.13)
project(untitled)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${untitled}/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#add_executable(trieMeta main.cpp subset_lb.cpp)

set(SOURCE_FILES main.cpp subset_lb.cpp)
add_executable(untitled ${SOURCE_FILES})