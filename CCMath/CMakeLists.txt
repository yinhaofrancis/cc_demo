cmake_minimum_required(VERSION 3.9)

project(CCMath VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_library(CCMath SHARED 
 "src/CCMath.cpp"
 "src/CCMath.h"
)

target_include_directories(CCMath PUBLIC src)