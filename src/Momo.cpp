/*
    Project: Momo's Quest (https://github.com/azazelm3dj3d/momo)
    Author: azazelm3dj3d (https://github.com/azazelm3dj3d)
    License: MIT
*/

#include "include/Momo.h"
#include "raymath.h"

Momo::Momo(int winWidth, int winHeight) : window_width(winWidth), window_height(winHeight) {
    texture_width = state.width / player_sprite_count;
    texture_height = state.height;
}

Vector2 Momo::get_screen_pos() {
    return Vector2 {
        static_cast<float>(window_width) / 2.0f - scale * (0.5f * texture_width),
        static_cast<float>(window_height) / 2.0f - scale * (0.5f * texture_height)
    };
}

void Momo::tick(float delta_time) {

    BaseCharacter::tick(delta_time);

    if (!get_alive()) { return; }

    // Key mapping for direction (velocity)
    if (IsKeyDown(KEY_W)) {
        velocity.y -= 1.0;
    }

    if (IsKeyPressed(KEY_F)) {
        ToggleFullscreen();
    }

    if (IsKeyDown(KEY_LEFT_SHIFT)) {

        if (k_speed < 10.0) {
            k_speed += 0.5;
        }

    } else {
        k_speed = 4.0;
    }
    
    if (IsKeyDown(KEY_A)) {
        velocity.x -= 1.0;
    }

    if (IsKeyDown(KEY_S)) {
        velocity.y += 1.0;
    }

    if (IsKeyDown(KEY_D)) {
        velocity.x += 1.0;
    }
}

void Momo::take_damage(float damage) {
    health -= damage;

    if (health <= 0.0f) {
        set_alive(false);
    }
}
