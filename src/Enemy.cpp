#include "Enemy.h"

#include <raylib.h>

#include <cmath>

#include "Config.h"

Enemy::Enemy(double x, double y) : x(x), y(y) { speed = 2; }

void Enemy::Draw() { DrawRectangle(x, y, Radius, Radius, BLUE); }

void Enemy::Update(double playerX, double playerY) {
    double dx = playerX - x;
    double dy = playerY - y;
    double dist = std::sqrt(dx * dx + dy * dy);
    if (dist > 0.01) {
        x += speed * (dx / dist);
        y += speed * (dy / dist);
    }
}
