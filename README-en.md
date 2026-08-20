# Roguelike

| **English** | [简体中文](README.md) |

A 2D Roguelike game project developed from scratch using **C++20 + raylib + CMake**.

---

## Project Overview

`Roguelike` is a 2D Roguelike game project currently being developed from scratch.

This project uses **raylib** as the underlying graphics and multimedia framework. Starting from the basic game loop, the project gradually builds a complete and maintainable game framework.

The project aims to implement:

- Game loop
- 2D rendering
- Player control
- Enemy system
- Combat system
- Collision detection
- Experience and leveling system
- Random skills and progression
- Maps and levels
- Boss battles
- Sound effects and background music
- Game save system
- UI system
- Complete Roguelike gameplay flow

The project is currently in the **early stage of development**.

---

## Tech Stack

- **C++20**
- **raylib 6.0**
- **CMake**
- **MinGW-w64 / GCC 16.2**
- **Git**
- **Visual Studio Code**

---

## Project Structure

```text
Roguelike/
├── assets/
│   └── icon/
│       ├── icon.ico
│       └── icon.rc
│
├── bin/
│   └── raylib.dll
│
├── build/
│   └── CMake build files
│
├── include/
│   ├── File.h
│   ├── Game.h
│   └── Player.h
│
├── src/
│   ├── File.cpp
│   ├── Game.cpp
│   ├── Player.cpp
│   └── main.cpp
│
├── CMakeLists.txt
├── README.md
├── README-en.md
└── .gitignore