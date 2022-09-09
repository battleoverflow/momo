#include "include/Environment.h"
#include "raymath.h"

Environment::Environment(Vector2 position, Texture2D tex) : world_pos(position), texture(tex) { }

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