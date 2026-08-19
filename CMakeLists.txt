cmake_minimum_required(VERSION 3.15)

project(Roguelike LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# raylib
set(RAYLIB_INCLUDE_DIR "C:/raylib-6.0_win64_mingw-w64/include")

add_executable(Roguelike WIN32
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
    src/File.cpp
    assets/icon/icon.rc
)

target_include_directories(Roguelike PRIVATE
    include
    ${RAYLIB_INCLUDE_DIR}
)

target_link_libraries(Roguelike PRIVATE
    raylibdll
)

target_compile_definitions(Roguelike PRIVATE
    UNICODE
    _UNICODE
)