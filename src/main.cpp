#include <iostream>
#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "raymath.h"
#include "log.h"

void gameLoop(bool debug_mode) {
    const int width{1280}; // Window width
    const int height{720}; // Window height

    std::string momo_version = "0.0.4";

    // Initialize raylib window
    InitWindow(width, height, ("Momo's Quest | v%s", momo_version.c_str()));

    // Loads map texture
    Texture2D map = LoadTexture("src/map/map.png");

    // Key mapping for speed (k_speed)
    float k_speed{4.0};

    // Load the main character
    Texture2D momo_idle = LoadTexture("src/textures/player/Idle.png");
    Texture2D momo_run = LoadTexture("src/textures/player/Run.png");
    Texture2D momo = LoadTexture("src/textures/player/Idle.png");

    float number_of_sprites{10.0f};

    // Sets Momo's position on the map
    Vector2 momo_pos {
        (float) width / 2.0f - 4.0f * (0.5f * (float) momo.width / number_of_sprites),
        (float) width / 2.0f - 4.0f * (0.5f * (float) momo.height)
    };

    // Direction schema:
    // 1 => right
    // -1 => left
    float dir_location{1.0f};

    // Animate Momo
    float running_time{};
    int cur_frame{};
    const int max_frames{6};
    const float update_time{1.0f / 12.0f};
    float delta_time{};

    SetTargetFPS(60); // Sets the frames per second

    Vector2 map_position{-900.0, -2300.0}; // Sets the map position

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
            
            // Changes direction of sprite (Momo)
            k_direction.x < 0.0f ? dir_location = -1.0f : dir_location = 1.0f;

            number_of_sprites = 8.0f;
            momo = momo_run;
        } else {
            number_of_sprites = 10.0f;
            momo = momo_idle;
        }

        // Map
        DrawTextureEx(map, map_position, 0.0, 4.0, WHITE);

        delta_time = GetFrameTime();

        // Animation Frame
        running_time += delta_time;

        if (running_time >= update_time) {
            cur_frame++; // Increments frames
            running_time = 0.0f; // Resets running time (+ resets spritesheet)

            if (cur_frame > max_frames) {
                cur_frame = 0; // Resets frame
            }
        }

        // Momo
        Rectangle start{cur_frame * (float) momo.width / number_of_sprites, 0.0f, dir_location * (float) momo.width / number_of_sprites, (float) momo.height};
        Rectangle finish{momo_pos.x, momo_pos.y, 4.0f * (float) momo.width / number_of_sprites, 4.0f * (float) momo.height};
        
        DrawTexturePro(momo, start, finish, Vector2{}, 0.0f, WHITE);

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