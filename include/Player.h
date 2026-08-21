#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

class Player {
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
    Player(double x, double y);
    ~Player();
    void LoadAssets();
    void Update();
    void Draw();
    double GetX() const;
    double GetY() const;
    void SetPosition(double newX, double newY);
};

#endif