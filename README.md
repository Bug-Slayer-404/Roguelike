# Roguelike

| [English](README-en.md) | **简体中文**|

一个使用 **C++20 + raylib + CMake** 从零开发的 2D Roguelike 游戏项目。

A 2D Roguelike game developed from scratch using **C++20 + raylib + CMake**.

---

## 项目简介

`Roguelike` 是一个正在从零开发中的 2D Roguelike 游戏项目。

本项目以 **raylib** 作为底层图形与多媒体框架，从基础游戏循环开始，逐步构建一个完整、可长期维护的游戏框架。

项目目标包括：

- 游戏主循环
- 2D 渲染
- 玩家控制
- 敌人系统
- 战斗系统
- 碰撞检测
- 经验与升级
- 随机技能与成长
- 地图与关卡
- Boss 战
- 音效与背景音乐
- 游戏存档
- UI 系统
- 完整的 Roguelike 游戏流程

项目目前处于**早期开发阶段**。

---

## 技术栈

- **C++20**
- **raylib 6.0**
- **CMake**
- **MinGW-w64 / GCC 16.2**
- **Git**
- **Visual Studio Code**

---

## 项目结构

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
│   └── CMake 构建文件
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