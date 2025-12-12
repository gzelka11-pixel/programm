cmake_minimum_required(VERSION 3.10)
project(Lab5)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включение директории с заголовочными файлами
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Создание исполняемого файла
add_executable(lab5
    main.cpp
    src/money_lib.cpp
)

# Для отладки можно добавить
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")