cmake_minimum_required(VERSION 3.16)
project(mov_test)

set(CMAKE_CXX_STANDARD 17)

add_executable(mov_test main.cpp omni.cpp omni.h errorhandling.h tcp.h utils.cpp utils.h)