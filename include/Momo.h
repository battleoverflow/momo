#pragma once

#include <iostream>
#include <stdio.h>
#include <string.h>

#include "raylib.h"

class Momo {
    public:
        Momo();
        // ~Momo();
        Vector2 get_world_pos() { return world_pos; }
        void set_screen_pos(int width, int height);
        void tick(float delta_time);
        bool debug_mode(bool debug_mode) {

            // I'm so sorry for anyone who sees this debug_mode()
            // TODO: Fix this - doesn't properly log debug methods for some reason
            int argc{};
            char* argv[2];

            if (argc == 2) {
                if (!strcmp(argv[1], "-d")) {
                    debug_mode = true;
                } else {
                    return -1;
                }
            
            } else {
                debug_mode = false;
            }

            return debug_mode;
        }
        
        void MomoInfoFloat(float debug_name) {
            printf("Momo's Quest [INFO_FLOAT]: %f\n", debug_name);
        }

        void MomoInfoInt(int debug_name) {
            printf("Momo's Quest [INFO_INT]: %i\n", debug_name);
        }
    private:
        Texture2D momo_state{LoadTexture("src/textures/player/Idle.png")};
        Texture2D momo_idle{LoadTexture("src/textures/player/Idle.png")};
        Texture2D momo_run{LoadTexture("src/textures/player/Run.png")};
        Vector2 screen_pos{}; // Coordinates of the player
        Vector2 world_pos{900.0, 2300.0}; // "Camera" attached to the player to allow movement (moves map, not player)
        float dir_location{1.0f}; // 1 => right & -1 => left

        // Animate Momo
        float running_time{};
        int cur_frame{};
        int max_frames{6};
        float update_time{1.0f / 12.0f};
        float delta_time{};
        float k_speed{4.0f};
        float number_of_sprites{10.0f};
        float texture_width{};
        float texture_height{};
};