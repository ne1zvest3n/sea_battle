cmake_minimum_required(VERSION 3.22.1)

project(sea_battle)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE
        sozvezdie_task.cpp)

add_executable(sea_battle sozvezdie_task.cpp)