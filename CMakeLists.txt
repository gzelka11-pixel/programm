cmake_minimum_required(VERSION 3.15)



set(PROJECT_NAME lab1)
project("$(PROJECT_NAME)")


set(CMAKE_CXX_STANDART 20)

add_executable("$(PROJECT_NAME)" main.cpp)