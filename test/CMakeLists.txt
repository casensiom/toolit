# Google Test (requerido)
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# Traer Google Test
FetchContent_MakeAvailable(googletest)


# Archivos fuente de pruebas
file(GLOB TEST_SOURCES *.cpp)

# Crear un ejecutable para las pruebas
add_executable(runTests ${TEST_SOURCES})

# Enlazar el ejecutable con la biblioteca util y GTest
target_link_libraries(runTests ${MAIN_PROJECT_NAME} gtest_main)

# Registrar las pruebas
add_test(NAME runTests COMMAND runTests)
