cmake_minimum_required(VERSION 3.26)
project(TBD_2023)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(TBD_2023
        Amazing.osm
        BlockedMap.osm
        output/main.exe
        Actions.cpp
        Actions.h
        main.cpp
        notepad.txt
        r_star_tree.cpp
        r_star_tree.hpp
        README.md)
