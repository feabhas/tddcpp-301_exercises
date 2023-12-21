cmake_minimum_required(VERSION 3.18)
project(host-gcc LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
    -Wall
    -Wextra
    -Wconversion
    -Wsign-conversion
    # -Werror
    $<$<CONFIG:DEBUG>:-g3>
    $<$<CONFIG:DEBUG>:-Og>
    $<$<CONFIG:RELEASE>:-O3>
)

add_compile_definitions(
    $<$<CONFIG:DEBUG>:DEBUG>
)

# WARNING: wildcards are expanded at generate time, not build time
# regenerate the build if new source files are added

# FILE (GLOB USER_SRC ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_subdirectory(src)

enable_testing()
add_subdirectory(tests)


