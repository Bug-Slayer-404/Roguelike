#ifndef GAME_H
#define GAME_H

#include <windows.h>

class Game {

public:

    Game(HINSTANCE hInstance, int nCmdShow);

    bool initialize();

    void run();

private:

    HINSTANCE hInstance;
    int nCmdShow;

    HWND hwnd;

};

#endif