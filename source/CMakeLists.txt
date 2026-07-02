cmake_minimum_required(VERSION 3.16)

project(
    Chip8
    VERSION 1.0
    LANGUAGES CXX
    )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)

add_executable(
    chip8
    main.cpp
    chip8.cpp
)

