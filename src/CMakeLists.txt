# Añadir todos los archivos fuente
file(GLOB_RECURSE UTIL_SOURCES *.cpp)

# Crear una biblioteca estática para utilidades
add_library(${MAIN_PROJECT_NAME} ${UTIL_SOURCES})
target_include_directories(${MAIN_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
message(" *** ADD CURRENT PATH: ${CMAKE_CURRENT_SOURCE_DIR}")
