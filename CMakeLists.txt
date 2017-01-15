cmake_minimum_required(VERSION 3.3)
project(Aspect)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/Aspect.h test/AopTest.h)
add_executable(Aspect ${SOURCE_FILES})