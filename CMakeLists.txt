cmake_minimum_required(VERSION 3.16)

project(
    Chip8
    VERSION 1.0
    LANGUAGES CXX
    )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

add_executable(
    chip8
    source/main.cpp
    source/chip8.cpp
)

target_include_directories(chip8 PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(chip8 PRIVATE ${SDL2_LIBRARIES})

