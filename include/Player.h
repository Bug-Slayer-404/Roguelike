#ifndef PLAYER_H
#define PLAYER_H

class Player {
   private:
    double x;
    double y;
    double speed;

   public:
    void Update();
    void Draw();
};

#endif