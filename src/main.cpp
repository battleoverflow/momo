/*
    Project: Momo's Quest (https://github.com/battleoverflow/momo)
    Author: battleoverflow (https://github.com/battleoverflow)
    License: MIT
*/

#include <iostream>
#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "raymath.h"
#include "include/Momo.h"
#include "include/Boss.h"
#include "include/Log.h"
#include "include/Environment.h"

/*
    TODO: FIX COLLISION DETECTION
*/

typedef enum GameScreen { MENU, GAME } GameScreen;

// Default scene set to the main menu
GameScreen currentScreen = MENU;

std::string momo_version = "0.1.0"; // Game version
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

void game_over() {
    DrawText(momo_version.c_str(), 20, 600, 30, MAROON);
    DrawText(title, 20, 650, 40, MAROON);
    DrawText("Game Over", width / 6, height / 3, 50, MAROON);
}

void game_loop(bool debug_mode) {
    // Initialize raylib window
    InitWindow(width, height, title);

    // Loads map texture
    Texture2D map = LoadTexture("assets/map.png");

    Vector2 map_pos{0.0, 0.0}; // Sets the map position
    const float map_scale{3.0}; // Sets the map's scale size (-smaller, +bigger)
    
    Momo momo{width, height};

    Environment environment[2] {
        Environment{Vector2{1050.0f, 500.0f}, LoadTexture("assets/textures/environment/Log.png")}, // Log location + texture load
        Environment{Vector2{1800.0f, 2000.0f}, LoadTexture("assets/textures/environment/Rock.png")} // Rock location + texture load
    };

    Boss boss {
        Vector2{},
        LoadTexture("assets/textures/enemies/Idle.png"),
        LoadTexture("assets/textures/enemies/Move.png"),
        LoadTexture("assets/textures/enemies/Attack.png"),
        LoadTexture("assets/textures/enemies/Death.png"),
    };

    // Sets the player as the target
    boss.set_target(&momo);
    
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

                if (!momo.get_alive()) {
                    game_over();
                    EndDrawing();
                    continue;
                } else {
                    std::string player_health = "Player Health: ";
                    player_health.append(std::to_string(momo.get_health()), 0, 5);
                    DrawText(player_health.c_str(), 55.0f, 45.0f, 40, RED);
                }

                if (boss.get_alive()) {
                    std::string enemy_health = "Enemy Health: ";
                    enemy_health.append(std::to_string(boss.get_health()), 0, 5);
                    DrawText(enemy_health.c_str(), 55.0f, 95.0f, 40, RED);
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

                boss.tick(GetFrameTime());

                if (IsKeyDown(KEY_Z)) {
                    if (CheckCollisionRecs(boss.get_collision_rec(), momo.get_collision_rec())) {
                        float damage = 20.0f;
                        boss.take_damage(damage * GetFrameTime());
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
