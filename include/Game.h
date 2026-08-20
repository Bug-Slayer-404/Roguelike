#ifndef GAME_H
#define GAME_H

#include "Enemy.h"
#include "Player.h"

class Game {
  private:
    Player player;
    Enemy enemy;
    void Update();
    void Draw();

  public:
    Game();
    void Run();
};

#endif