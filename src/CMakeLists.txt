# Add all source files
file(GLOB_RECURSE UTIL_SOURCES *.cpp)

# Build an static library
add_library(${MAIN_PROJECT_NAME} ${UTIL_SOURCES})
target_include_directories(${MAIN_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})



