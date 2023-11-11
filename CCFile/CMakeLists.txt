cmake_minimum_required(VERSION 3.9.0)

project(CCFile VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_library(CCFile
    "src/CCFile.h"
    "src/CCFile.cpp"
)

target_include_directories(CCFile PUBLIC src)