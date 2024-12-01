cmake_minimum_required(VERSION 3.10)

option(CMAKE_EXPORT_COMPILE_COMMANDS "CMAKE_EXPORT_COMPILE_COMMANDS" ON)

# Nombre del proyecto
set(MAIN_PROJECT_NAME "toolit")
project(${MAIN_PROJECT_NAME})

# Establecer el estándar de C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Añadir el directorio fuente
add_subdirectory(src)

# Añadir los tests
enable_testing()
add_subdirectory(test)
