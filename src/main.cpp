#include <iostream>
#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "raymath.h"
#include "include/Log.h"
#include "include/Momo.h"

void game_loop() {
    std::string momo_version = "0.0.5";

    const int width{1280}; // Window width
    const int height{720}; // Window height
    const char* title = "Momo's Quest"; // Window title
    // const char* title = "Momo's Quest | v%s", momo_version.c_str(); // Window title

    // Initialize raylib window
    InitWindow(width, height, title);

    // Loads map texture
    Texture2D map = LoadTexture("src/map/map.png");

    SetTargetFPS(60); // Sets the frames per second

    Vector2 map_pos{0.0, 0.0}; // Sets the map position

    Momo momo;

    momo.set_screen_pos(width, height);

    // Checks if the window is open/closed
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        // Movement handler for the player
        map_pos = Vector2Scale(momo.get_world_pos(), -1.0f);

        // Map
        DrawTextureEx(map, map_pos, 0.0, 4.0, WHITE);
        
        momo.tick(GetFrameTime());

        EndDrawing();
    }

    CloseWindow();
}

int main(int argc, char* argv[]) {

    if (argc == 2) {
        if (!strcmp(argv[1], "-d")) {
            MomoInfo("Running in DEBUG mode!");
            game_loop();
        } else {
            MomoError("Please provide the correct argument (-d) or run without any arguments");
            return -1;
        }
    
    } else {
        game_loop();
    }

    return 0;
}