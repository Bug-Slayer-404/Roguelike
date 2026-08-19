#include "Game.h"

Game::Game(HINSTANCE hInstance, int nCmdShow)
    : hInstance(hInstance),
      nCmdShow(nCmdShow),
      hwnd(nullptr) {
}

bool Game::initialize() {

    const wchar_t CLASS_NAME[] = L"RoguelikeWindow";

    WNDCLASS wc = {};

    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    if (!RegisterClass(&wc)) {
        return false;
    }

    hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Roguelike",
        WS_OVERLAPPEDWINDOW,

        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1280,
        720,

        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (hwnd == nullptr) {
        return false;
    }

    ShowWindow(hwnd, nCmdShow);

    return true;
}

void Game::run() {

    MSG msg = {};

    while (GetMessage(&msg, nullptr, 0, 0) > 0) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);

    }
}