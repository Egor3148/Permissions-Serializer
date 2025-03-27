# Минимальная требуемая версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(PermsSerializer LANGUAGES CXX)

option(USE_FLTK "Build with FLTK GUI" ON)  # Опция для включения/выключения GUI

# Установка стандарта C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Добавление папки с заголовочными файлами
include_directories(inc)

# Список исходных файлов
set(SOURCES
    src/aes.cpp
    src/main.cpp
    src/encrypter.cpp
    src/perms_manip.cpp
    src/perms_serializer.cpp
    src/cli_interface.cpp
    src/gui_interface.cpp
)

# Создание исполняемого файла
if(USE_FLTK)
    add_subdirectory(fltk)
    add_executable(PermsSerializer ${SOURCES} fltk)

    # Связывание с FLTK и его зависимостями
    target_link_libraries(PermsSerializer
        fltk  # Основная библиотека FLTK
        fltk_images  # Для работы с изображениями (если нужно)
        fltk_gl     # Для OpenGL (если нужно)
    )

    target_compile_definitions(PermsSerializer PRIVATE USE_FLTK)
else()
    message(STATUS "Building in CLI mode (without FLTK)")
    add_executable(PermsSerializer ${SOURCES})
endif()