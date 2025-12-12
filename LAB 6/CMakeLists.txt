cmake_minimum_required(VERSION 3.10)
project(Rectangle2D_Demo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создаем исполняемый файл
add_executable(RectangleDemo
    main.cpp
    src/Rectangle2D.cpp
)

# Указываем путь к заголовочным файлам
target_include_directories(RectangleDemo PRIVATE include)

# Опции компиляции для MinGW
if(MINGW)
    add_compile_options(-Wall -Wextra)
endif()