cmake_minimum_required(VERSION 3.15)
project(CMakeProject2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BINARY_DIR /path/to/build)

add_executable(
    main.cpp
    Rectangle2D.cpp
)
