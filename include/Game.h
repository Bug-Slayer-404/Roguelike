#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game {
  private:
    Player player;
    void Update();
    void Draw();

  public:
    Game();
    void Run();
};

#endif