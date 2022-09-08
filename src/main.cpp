#include <iostream>
#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "raymath.h"
#include "include/Momo.h"
#include "include/Log.h"
#include "include/Environment.h"

void game_loop(bool debug_mode) {
    std::string momo_version = "0.0.6";

    const int width{1280}; // Window width
    const int height{720}; // Window height
    const char* title = "Momo's Quest"; // Window title
    // const char* title = "Momo's Quest | v%s", momo_version.c_str(); // Window title

    // Initialize raylib window
    InitWindow(width, height, title);

    // Loads map texture
    Texture2D map = LoadTexture("src/map/map.png");

    Vector2 map_pos{0.0, 0.0}; // Sets the map position
    const float map_scale{3.0}; // Sets the map's scale size (-smaller, +bigger)
    
    Momo momo{width, height};

    Environment environment[2] {
        Environment{Vector2{1050.0f, 500.0f}, LoadTexture("src/textures/environment/Log.png")}, // Log location + texture load
        Environment{Vector2{1800.0f, 2000.0f}, LoadTexture("src/textures/environment/Rock.png")} // Rock location + texture load
    };
    
    SetTargetFPS(60); // Sets the frames per second

    // Checks if the window is open/closed
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        // Movement handler for the player
        map_pos = Vector2Scale(momo.get_world_pos(), -1.0f);

        // Map
        DrawTextureEx(map, map_pos, 0.0, map_scale, WHITE);

        // Environment handler
        for (auto env : environment) {
            env.render(momo.get_world_pos());
        }

        momo.tick(GetFrameTime());

        if (debug_mode) {
            // TODO: Make FPS real-time, not hard set
            DrawFPS(10, 10);

            // Check for map boundaries
            if (momo.get_world_pos().x < 0.0f ||
                momo.get_world_pos().y < 0.0f ||
                momo.get_world_pos().x + width > map.width * map_scale ||
                momo.get_world_pos().y + height > map.height * map_scale) {

                MomoWarning("OUT OF BOUNDS! :O\n");
            }
        } else {
            // Check for map boundaries
            if (momo.get_world_pos().x < 0.0f ||
                momo.get_world_pos().y < 0.0f ||
                momo.get_world_pos().x + width > map.width * map_scale ||
                momo.get_world_pos().y + height > map.height * map_scale) {
                
                momo.undo_movement();
                MomoWarning("OUT OF BOUNDS! :O\n");
            }
        }

        // Environment collisions
        for (auto env : environment) {
            if (CheckCollisionRecs(env.get_collision_rec(momo.get_world_pos()), momo.get_collision_rec())) {
                momo.undo_movement();
            }
        }


        EndDrawing();
    }

    CloseWindow();
}

int main(int argc, char* argv[]) {

    if (argc == 2) {
        if (!strcmp(argv[1], "-d")) {
            MomoInfo("Running in DEBUG mode!");
            game_loop(true);

        } else {
            MomoError("Please provide the correct argument (-d) or run without any arguments");
            return -1;
        }
    
    } else {
        game_loop(false);
    }

    return 0;
}