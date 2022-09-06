#include <iostream>
#include "raylib.h"
#include "raymath.h"

void gameLoop() {
    const int width{1280}; // Window width
    const int height{720}; // Window height

    // Initialize raylib window
    InitWindow(width, height, "Momo's Quest | v0.0.1");

    // Loads map texture
    Texture2D map = LoadTexture("src/map/map.png");

    SetTargetFPS(60); // Sets the frames per second

    // Checks if the window is open/closed
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 map_position{0.0, 0.0}; // Sets the map position

        DrawTextureEx(map, map_position, 0.0, 4.0, WHITE); // Draw the map

        EndDrawing();
    }

    CloseWindow();
}

int main() {
    gameLoop();
    return 0;
}