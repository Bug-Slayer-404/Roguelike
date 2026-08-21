#include "Player.h"

#include <raylib.h>

#include "Config.h"

Player::Player(double x, double y) : x(x), y(y) { speed = 5; }

void Player::Draw() { DrawRectangle(x, y, Radius, Radius, RED); }

void Player::Update() {
    // move the player based on input
    if (IsKeyDown(KEY_A)) {
        x -= speed;
    }
    if (IsKeyDown(KEY_D)) {
        x += speed;
    }
    if (IsKeyDown(KEY_W)) {
        y -= speed;
    }
    if (IsKeyDown(KEY_S)) {
        y += speed;
    }
    if (0 > x) x = 0;
    if (x > WindowWidth - Radius) x = WindowWidth - Radius;
    if (0 > y) y = 0;
    if (y > WindowLength - Radius) y = WindowLength - Radius;

    // attach the player to the mouse position if KEY_K is pressed
    /*
    if (IsKeyDown(KEY_K)) {
        x = GetMouseX();
        y = GetMouseY();
    }
    */
}

double Player::GetX() const { return x; }

double Player::GetY() const { return y; }