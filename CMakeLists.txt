cmake_minimum_required(VERSION 3.26)
project(seaport)

set(CMAKE_CXX_STANDARD 17)

add_executable(seaport main.cpp
        Ship.cpp
        Ship.h
        globals.cpp
        globals.h
        generator.cpp
        readfile.cpp
        generator.cpp
        generator.h
        readfile.h
        write_file.cpp
        write_file.h
        Ship_in_queue.cpp
        Ship_in_queue.h
        modelling.cpp
        modelling.h
        vizualization.cpp
        vizualization.h
)
