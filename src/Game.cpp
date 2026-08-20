#include "Game.h"

#include <raylib.h>

#include "Config.h"
#include "Player.h"

Game::Game()
    : player(WindowWidth / 2.0 - Radius, WindowLength / 2.0 - Radius) {}

void Game::Run() {
    InitWindow(WindowWidth, WindowLength, WindowTitle);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        Update();
        Draw();
    }

    CloseWindow();
}

void Game::Update() { player.Update(); }

void Game::Draw() {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    player.Draw();

    EndDrawing();
}