cmake_minimum_required(VERSION 3.26)
project(seaport)

set(CMAKE_CXX_STANDARD 17)

add_executable(seaport main.cpp
        src/Ship.cpp
        include/Ship.h
        src/globals.cpp
        include/globals.h
        src/generator.cpp
        src/readfile.cpp
        src/generator.cpp
        include/generator.h
        include/readfile.h
        src/write_file.cpp
        include/write_file.h
        src/Ship_in_queue.cpp
        include/Ship_in_queue.h
        src/modelling.cpp
        include/modelling.h
        src/vizualization_modelling_ships.cpp
        include/vizualization_modelling_ships.h
        src/vizualization_types.cpp
        include/vizualization_types.h
        src/vizualization.cpp
        include/vizualization.h
)
