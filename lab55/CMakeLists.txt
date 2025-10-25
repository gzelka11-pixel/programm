cmake_minimum_required(VERSION 3.15)
project(lab55)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 20)

# Список исходных файлов
set(SOURCES 
    main.cpp
    money.cpp
    calculator.cpp
)

# Создаем исполняемый файл
add_executable(money_app main.cpp money.cpp)