# Минимальная требуемая версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(PermsSerializer LANGUAGES CXX)

# Установка стандарта C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Добавление папки с заголовочными файлами
include_directories(inc)

# Список исходных файлов
set(SOURCES
    "src/aes.cpp"
    src/main.cpp
    src/encrypter.cpp
    src/perms_manip.cpp
    src/perms_serializer.cpp
)

# Создание исполняемого файла
add_executable(PermsSerializer ${SOURCES})