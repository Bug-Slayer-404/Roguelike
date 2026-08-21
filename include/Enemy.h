#ifndef ENEMY_H
#define ENEMY_H

#include <raylib.h>

class Enemy {
  private:
    double x;
    double y;
    double speed;
    Texture2D texture;
    int frame;
    double animationTime;
    bool isMoving;
    bool facingRight;

  public:
    Enemy(double x, double y);
    ~Enemy();
    void LoadAssets();
    void Update(double playerX, double playerY);
    void Draw();
    double GetX() const;
    double GetY() const;
    void SetPosition(double newX, double newY);
};

#endif
