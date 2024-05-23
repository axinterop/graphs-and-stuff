cmake_minimum_required(VERSION 3.28)
project(project3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(project3
        main.cpp
        Graph.cpp
        Graph.h
        Vertex.h
        Vertex.cpp
)
