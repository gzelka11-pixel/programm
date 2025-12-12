cmake_minimum_required(VERSION 3.10)
project(NotificationList)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Исходные файлы
set(SOURCES
    src/main.cpp
    src/list.cpp
)

# Заголовочные файлы
set(HEADERS
    include/list.h
)

# Исполняемый файл
add_executable(notification_list ${SOURCES} ${HEADERS})

# Указываем директории для заголовочных файлов
target_include_directories(notification_list PRIVATE include)

# Для корректного поиска файлов данных
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)