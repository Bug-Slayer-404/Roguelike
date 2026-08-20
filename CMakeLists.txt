cmake_minimum_required(VERSION 3.15)

project(Roguelike LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/bin"
)

set(RAYLIB_DIR
    "C:/raylib-6.0_win64_mingw-w64"
)

set(RAYLIB_INCLUDE_DIR
    "${RAYLIB_DIR}/include"
)

set(RAYLIB_LIB_DIR
    "${RAYLIB_DIR}/lib"
)

add_executable(Roguelike
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
    src/Enemy.cpp
    src/File.cpp
    assets/icon/icon.rc
)

target_include_directories(Roguelike PRIVATE
    include
    "${RAYLIB_INCLUDE_DIR}"
)

target_link_directories(Roguelike PRIVATE
    "${RAYLIB_LIB_DIR}"
)

target_link_libraries(Roguelike PRIVATE
    raylibdll
)

target_compile_definitions(Roguelike PRIVATE
    UNICODE
    _UNICODE
)