#include <iostream>
#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "raymath.h"
#include "include/Momo.h"
#include "include/Log.h"
#include "include/Environment.h"

/*
    TODO: FIX COLLISION DETECTION
*/

typedef enum GameScreen { MENU, GAME } GameScreen;

// Default scene set to the main menu
GameScreen currentScreen = MENU;

std::string momo_version = "0.0.9"; // Game version
const int width{1280}; // Window width
const int height{720}; // Window height
const char* title = "Momo's Quest"; // Window title

void main_menu() {
    ClearBackground(BLACK);
    DrawText(momo_version.c_str(), 20, 600, 30, MAROON);
    DrawText(title, 20, 650, 40, MAROON);
    DrawText("Press Enter or Space to PLAY", width / 6, height / 3, 50, MAROON);

    // Changes the scene when the enter key or space key is pressed
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
        currentScreen = GAME;
    }
}

void game_loop(bool debug_mode) {
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

    printf("\nRunning Momo's Quest v%s\n", momo_version.c_str());

    // Checks if the window is open/closed
    while (!WindowShouldClose()) {
        BeginDrawing();

        switch (currentScreen) {
            case MENU: {
                main_menu();
            } break;
            case GAME: {
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

                // Check for map boundaries
                if (momo.get_world_pos().x < 0.0f ||
                    momo.get_world_pos().y < 0.0f ||
                    momo.get_world_pos().x + width > map.width * map_scale ||
                    momo.get_world_pos().y + height > map.height * map_scale) {
                    
                    if (debug_mode) {
                        momo.stop_movement();
                        MomoWarning("OUT OF BOUNDS!\n");
                    }
                }

                // Environment collisions
                for (auto env : environment) {
                    if (CheckCollisionRecs(env.get_collision_rec(momo.get_world_pos()), momo.get_collision_rec())) {

                        if (debug_mode) {
                            momo.stop_movement();
                        }
                    }
                }
            } break;
        }

        EndDrawing();
    }

    CloseWindow();

    if (debug_mode) {
        momo.unload_textures();
        MomoInfo("Successfully unloaded textures");
    } else {
        momo.unload_textures();
    }

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