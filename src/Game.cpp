#include "Game.h"
#include "Player.h"

#include <raylib.h>

#define WindowWidth 1280
#define Windowlength 720
#define WindowTitle "Roguelike"

void Game::Run() {
  InitWindow(WindowWidth, Windowlength, WindowTitle);

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    Update();
    Draw();
  }

  CloseWindow();
}

void Game::Update() {}

void Game::Draw() {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  DrawRectangle(100, 100, 50, 50, RED);
  DrawText("Success", 40, 40, 40, PINK);

  EndDrawing();
}