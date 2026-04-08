cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(websocket)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

add_executable(websocket
    ./main.cpp
)

target_compile_options(websocket PRIVATE -Wall -Wextra -Wconversion -Wpedantic -Wimplicit-fallthrough)
