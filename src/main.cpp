#include <windows.h>

#include "Game.h"

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPSTR,
    int nCmdShow
) {
    Game game(hInstance, nCmdShow);

    if (!game.initialize()) {
        return 1;
    }

    game.run();

    return 0;
}