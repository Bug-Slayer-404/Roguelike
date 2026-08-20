#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
  private:
    double x;
    double y;
    double speed;

  public:
    Enemy(double x, double y);
    void Update(double playerX, double playerY);
    void Draw();
};

#endif
