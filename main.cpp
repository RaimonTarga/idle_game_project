#include "raylib.h"
#include "Game.h"

int main() {
    InitWindow(800, 600, "Idle ARPG Prototype :3");

    // Make borderless and topmost
    SetWindowState(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TOPMOST);

    // Resize to full monitor resolution
    int screenWidth = GetMonitorWidth(0);
    int screenHeight = GetMonitorHeight(0);
    SetWindowSize(screenWidth, screenHeight);

    // Anchor to top-left corner
    SetWindowPosition(0, 0);

    SetTargetFPS(60);

    Game game({0, 0});
    game.Init();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        game.Update(dt);
        game.Draw();
    }

    CloseWindow();
    return 0;
}
