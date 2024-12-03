cmake_minimum_required(VERSION 3.10)

set(MAIN_PROJECT_NAME "toolit")
project(${MAIN_PROJECT_NAME})

option(CMAKE_EXPORT_COMPILE_COMMANDS "CMAKE_EXPORT_COMPILE_COMMANDS" ON)
option(COVERAGE_ENABLED "Enables coverage report" OFF)

# Support coverage
if(COVERAGE_ENABLED)
    message(STATUS "Coverage enabled")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
        set(CMAKE_COMPILER_IS_CLANGXX 1)
    endif()

    if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
        if(CMAKE_COMPILER_IS_GNUCXX)
            link_libraries(gcov)
        endif()

        if(CMAKE_COMPILER_IS_GNUCXX)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
        else()
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -fprofile-arcs -ftest-coverage -fprofile-instr-generate -fcoverage-mapping")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fprofile-arcs -ftest-coverage -fprofile-instr-generate -fcoverage-mapping")
        endif()
    else()
        message(STATUS "[WARN] Coverage was enabled but compiler doesn't support it.")
    endif()
endif()



# Configure C++ options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source code folder
add_subdirectory(src)

# Add test folder
enable_testing()
add_subdirectory(test)
