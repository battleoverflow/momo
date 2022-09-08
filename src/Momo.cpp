#include "include/Momo.h"
#include "raymath.h"

Momo::Momo(int winWidth, int winHeight) {
    texture_width = momo_state.width / number_of_sprites;
    texture_height = momo_state.height;

    screen_pos = {
        static_cast<float>(winWidth) / 2.0f - texture_scale * (0.5f * texture_width),
        static_cast<float>(winHeight) / 2.0f - texture_scale * (0.5f * texture_height)
    };
}

void Momo::tick(float delta_time) {
    world_pos_last_frame = world_pos;

    // Key mapping for direction (k_direction)
    Vector2 k_direction{};

    if (IsKeyDown(KEY_W)) {
        k_direction.y -= 1.0;
    }

    if (IsKeyPressed(KEY_F)) {
        ToggleFullscreen();
    }

    if (IsKeyDown(KEY_LEFT_SHIFT)) {

        if (k_speed < 10.0) {
            k_speed += 0.5;

            if (debug_mode(true)) {
                Momo::MomoInfoFloat(k_speed);
            }
        }

    } else {
        k_speed = 4.0;
    }
    
    if (IsKeyDown(KEY_A)) {
        k_direction.x -= 1.0;
    }

    if (IsKeyDown(KEY_S)) {
        k_direction.y += 1.0;
    }

    if (IsKeyDown(KEY_D)) {
        k_direction.x += 1.0;
    }

    if (Vector2Length(k_direction) != 0.0) {
        // Sets the new map position based on the direction being pressed and normalizes the vector
        world_pos = Vector2Add(world_pos, Vector2Scale(Vector2Normalize(k_direction), k_speed));
        
        // Changes direction of sprite (Momo)
        k_direction.x < 0.0f ? dir_location = -1.0f : dir_location = 1.0f;

        number_of_sprites = 8.0f;
        momo_state = momo_run;
    } else {
        number_of_sprites = 10.0f;
        momo_state = momo_idle;
    }

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
    Rectangle start{cur_frame * texture_width, 0.0f, dir_location * texture_width, texture_height};
    Rectangle finish{screen_pos.x, screen_pos.y, texture_scale * texture_width, texture_scale * texture_height};

    DrawTexturePro(momo_state, start, finish, Vector2{}, 0.0f, WHITE);
}

void Momo::undo_movement() {
    world_pos = world_pos_last_frame;
}

Rectangle Momo::get_collision_rec() {

    // Collision detection (rec)
    return Rectangle {
        screen_pos.x,
        screen_pos.y,
        texture_width * texture_scale,
        texture_height * texture_scale
    };
}