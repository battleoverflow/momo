/*
    Project: Momo's Quest (https://github.com/azazelm3dj3d/momo)
    Author: azazelm3dj3d (https://github.com/azazelm3dj3d)
    License: MIT
*/

#include "include/BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter() { }

void BaseCharacter::stop_movement() {
    world_pos = world_pos_last_frame;
}

Rectangle BaseCharacter::get_collision_rec() {

    // Collision detection (rec)
    return Rectangle {
        get_screen_pos().x,
        get_screen_pos().y,
        texture_width * scale,
        texture_height * scale
    };
}

void BaseCharacter::tick(float delta_time) {
    world_pos_last_frame = world_pos;

    // Animation Frame
    running_time += delta_time;

    if (running_time >= update_time) {
        cur_frame++; // Increments frames
        running_time = 0.0f; // Resets running time (+ resets spritesheet)

        if (cur_frame > max_frames) {
            cur_frame = 0; // Resets frame
        }
    }

    if (Vector2Length(velocity) != 0.0) {
        // Sets the new map position based on the direction being pressed and normalizes the vector
        world_pos = Vector2Add(world_pos, Vector2Scale(Vector2Normalize(velocity), k_speed));
        
        // Changes direction of sprite (Momo)
        velocity.x < 0.0f ? dir_location = -1.0f : dir_location = 1.0f;

        player_sprite_count = 8.0f;
        state = run;
    } else {
        player_sprite_count = 10.0f;
        state = idle;

        // Only allowed to attack if idle
        if (IsKeyDown(KEY_Z)) {
            player_sprite_count = 6.0f;
            state = attack;
        }
    }

    if (!get_alive()) {
        state = death;
        player_sprite_count = 10.0f;
        enemy_sprite_count = 5.0f;
    }

    velocity = {};

    // Texture
    Rectangle start{cur_frame * texture_width, 0.0f, dir_location * texture_width, texture_height};
    Rectangle finish{get_screen_pos().x, get_screen_pos().y, scale * texture_width, scale * texture_height};

    DrawTexturePro(state, start, finish, Vector2{}, 0.0f, WHITE);
}

void BaseCharacter::unload_textures() {
    UnloadTexture(state);
    UnloadTexture(idle);
    UnloadTexture(run);
    UnloadTexture(attack);
    UnloadTexture(death);
}
