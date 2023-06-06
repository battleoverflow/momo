#include "include/Boss.h"
#include "raymath.h"

Boss::Boss(Vector2 pos, Texture2D idle_tex, Texture2D run_tex, Texture2D death_tex) {

    world_pos = pos;
    state = idle_tex;
    idle = idle_tex;
    run = run_tex;
    dead = death_tex;
    
    texture_width = state.width / enemy_sprite_count;
    texture_height = state.height;
    k_speed = 4.5f;
}

void Boss::tick(float delta_time) {

    if (!get_alive()) { return; }

    // Locate the player
    velocity = Vector2Subtract(target->get_screen_pos(), get_screen_pos());

    BaseCharacter::tick(delta_time);

    if (CheckCollisionRecs(target->get_collision_rec(), get_collision_rec())) {
        target->take_damage(dps * delta_time);
    }
}

Vector2 Boss::get_screen_pos() {
    // Sets the initial position of the enemy
    return Vector2Subtract(world_pos, target->get_world_pos());
}