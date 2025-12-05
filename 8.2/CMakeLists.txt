cmake_minimum_required(VERSION 3.15)
project(TextProcessor)

set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем исполняемый файл, указывая пути к исходным файлам
add_executable(TextProcessor 
    src/main.cpp 
    src/text_processor.cpp
)

# Указываем, где искать заголовочные файлы
target_include_directories(TextProcessor PRIVATE include)