#include <iostream>
#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "raymath.h"
#include "log.h"

void gameLoop(bool debug_mode) {
    const int width{1280}; // Window width
    const int height{720}; // Window height

    std::string momo_version = "0.0.2";

    // Initialize raylib window
    InitWindow(width, height, ("Momo's Quest | v%s", momo_version.c_str()));

    // Loads map texture
    Texture2D map = LoadTexture("src/map/map.png");

    // Key mapping for speed (k_speed)
    float k_speed{4.0};

    SetTargetFPS(60); // Sets the frames per second

    Vector2 map_position{0.0, 0.0}; // Sets the map position

    // Checks if the window is open/closed
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        // Key mapping for direction (k_direction)
        Vector2 k_direction{};

        if (IsKeyDown(KEY_W)) {
            k_direction.y -= 1.0;

            if (debug_mode) {
                MomoInfo("W");
            }
        }
        
        if (IsKeyDown(KEY_A)) {
            k_direction.x -= 1.0;

            if (debug_mode) {
                MomoInfo("A");
            }
        }

        if (IsKeyDown(KEY_S)) {
            k_direction.y += 1.0;
            
            if (debug_mode) {
                MomoInfo("S");
            }
        }

        if (IsKeyDown(KEY_D)) {
            k_direction.x += 1.0;
            
            if (debug_mode) {
                MomoInfo("D");
            }
        }

        if (Vector2Length(k_direction) != 0.0) {
            // Sets the new map position based on the direction being pressed and normalizes the vector
            map_position = Vector2Subtract(map_position, Vector2Scale(Vector2Normalize(k_direction), k_speed));
        }

        DrawTextureEx(map, map_position, 0.0, 4.0, WHITE); // Draw the map

        EndDrawing();
    }

    CloseWindow();
}

int main(int argc, char* argv[]) {

    if (argc == 2) {
        if (!strcmp(argv[1], "-d")) {
            MomoInfo("Running in DEBUG mode!");
            gameLoop(true);
        } else {
            MomoError("Please provide the correct argument (-d) or run without any arguments");
            return -1;
        }
    
    } else {
        gameLoop(false);
    }

    return 0;
}