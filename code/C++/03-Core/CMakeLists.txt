cmake_minimum_required(VERSION 3.23)
project(03_Core)

set(CMAKE_CXX_STANDARD 14)

add_executable(03_Core main.cpp header_files/Point.h Point.cpp header_files/Circle.h Circle.cpp computer.cpp)
