/*
    Project: Momo's Quest (https://github.com/azazelm3dj3d/momo)
    Author: azazelm3dj3d (https://github.com/azazelm3dj3d)
    License: MIT
*/

#include "include/Environment.h"
#include "raymath.h"

Environment::Environment(Vector2 position, Texture2D tex) : texture(tex), world_pos(position) { }

void Environment::render(Vector2 momo_pos) {
    Vector2 screen_pos{Vector2Subtract(world_pos, momo_pos)};
    DrawTextureEx(texture, screen_pos, 0.0f, scale, WHITE);
}

Rectangle Environment::get_collision_rec(Vector2 momo_pos) {
    Vector2 screen_pos{Vector2Subtract(world_pos, momo_pos)};

    // Collision detection (rec)
    return Rectangle {
        screen_pos.x,
        screen_pos.y,
        texture.width * scale,
        texture.height * scale
    };
}
