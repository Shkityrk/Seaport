cmake_minimum_required(VERSION 3.26)
project(seaport)

set(CMAKE_CXX_STANDARD 17)

add_executable(seaport main.cpp
        Ship.cpp
        Ship.h
        globals.cpp
        globals.h
)
