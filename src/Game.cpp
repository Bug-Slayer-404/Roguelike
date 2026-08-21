#include "Game.h"

#include <raylib.h>

#include <cmath>

#include "Config.h"
#include "Player.h"

Game::Game()
    : player(WindowWidth / 2.0, WindowLength / 2.0),
      enemy(GetRandomValue(0, WindowWidth - CharacterSize),
            GetRandomValue(0, WindowLength - CharacterSize)) {}

void Game::Run() {
    InitWindow(WindowWidth, WindowLength, WindowTitle);

    player.LoadAssets();
    enemy.LoadAssets();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        Update();
        Draw();
    }

    CloseWindow();
}

void Game::Update() {
    player.Update();

    const double dx = player.GetX() - enemy.GetX();
    const double dy = player.GetY() - enemy.GetY();
    const double dist = std::sqrt(dx * dx + dy * dy);
    const double hitboxSize = CharacterSize * 0.7;

    if (dist < hitboxSize) {
        const double nx = (dist > 0.0001) ? dx / dist : 1.0;
        const double ny = (dist > 0.0001) ? dy / dist : 0.0;
        const double overlap = (hitboxSize - dist) * 0.5;

        player.SetPosition(player.GetX() + nx * overlap,
                           player.GetY() + ny * overlap);
        enemy.SetPosition(enemy.GetX() - nx * overlap,
                          enemy.GetY() - ny * overlap);
    }

    enemy.Update(player.GetX(), player.GetY());
}

void Game::Draw() {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    enemy.Draw();
    player.Draw();

    EndDrawing();
}