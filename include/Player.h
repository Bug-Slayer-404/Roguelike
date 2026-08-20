#ifndef PLAYER_H
#define PLAYER_H

class Player {
  private:
    double x;
    double y;
    double speed;

  public:
    Player(double x, double y);
    void Update();
    void Draw();
    double GetX() const;
    double GetY() const;
};

#endif