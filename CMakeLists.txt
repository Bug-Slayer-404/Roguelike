cmake_minimum_required(VERSION 3.15)

project(Roguelike LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Roguelike WIN32
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
    src/File.cpp
    resource/icon.rc
)

target_include_directories(Roguelike PRIVATE
    include
)

target_compile_definitions(Roguelike PRIVATE
    UNICODE
    _UNICODE
)