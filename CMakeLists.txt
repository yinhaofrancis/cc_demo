cmake_minimum_required(VERSION 3.5.0)
project(CC_Math_Demo VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_subdirectory(CCMath)

add_subdirectory(CCFile)

add_subdirectory(CCSocket)

add_executable(CC_Math_Demo main.cpp)

target_link_libraries(CC_Math_Demo CCMath CCFile CCSocket)