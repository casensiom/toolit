find_package(GTest)
if(GTEST_LIBRARY)
    include_directories(${GTEST_INCLUDE_DIRS})
    set(gtestlib GTest::GTest)
else()
    message(STATUS "GTest not found, manage to download it.")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    set(gtestlib gtest_main)
endif()

# Add all source files
file(GLOB TEST_SOURCES *.cpp)

set(TEST_PROJECT_NAME ${MAIN_PROJECT_NAME}_test)

# Build an executable binary
add_executable(${TEST_PROJECT_NAME} ${TEST_SOURCES})

# Link the binary with the library and gtest
target_link_libraries(${TEST_PROJECT_NAME} ${MAIN_PROJECT_NAME} ${gtestlib})

# Register tests
add_test(NAME ${TEST_PROJECT_NAME} COMMAND ${TEST_PROJECT_NAME})
