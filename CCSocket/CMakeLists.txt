cmake_minimum_required(VERSION 3.9)

project(CCSocket VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_library(CCSocket SHARED 
 "src/CCSocket.cpp"
 "src/CCSocket.h"
)

target_include_directories(CCSocket PUBLIC src)