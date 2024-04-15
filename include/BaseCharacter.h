/*
    Project: Momo's Quest (https://github.com/battleoverflow/momo)
    Author: battleoverflow (https://github.com/battleoverflow)
    License: MIT
*/


#ifndef BASE_CHARACTER_H
    #define BASE_CHARACTER_H

    #include "raylib.h"

    class BaseCharacter {
        public:
            BaseCharacter();
            Vector2 get_world_pos() { return world_pos; }
            void stop_movement();
            void unload_textures();
            Rectangle get_collision_rec();
            virtual void tick(float delta_time);
            virtual Vector2 get_screen_pos() = 0;
            bool get_alive() { return alive; }
            void set_alive(bool is_alive) { alive = is_alive; }
        
        protected:
            Texture2D state{LoadTexture("assets/textures/player/Idle.png")};
            Texture2D idle{LoadTexture("assets/textures/player/Idle.png")};
            Texture2D run{LoadTexture("assets/textures/player/Run.png")};
            Texture2D attack{LoadTexture("assets/textures/player/Attack.png")};
            Texture2D death{LoadTexture("assets/textures/player/Death.png")};
            Vector2 world_pos{530.0, 1500.0}; // "Camera" attached to the player to allow movement (moves map, not player)
            Vector2 world_pos_last_frame{}; // Checks for last frame to check map boundaries and collisions

            // Animate textures
            int max_frames{6};
            int cur_frame{};
            float dir_location{1.0f}; // 1 => right & -1 => left
            float running_time{};
            float update_time{1.0f / 12.0f};
            float delta_time{};
            float k_speed{4.0f};
            float texture_width{};
            float texture_height{};
            float scale{4.0f};
            float player_sprite_count{10.0f};
            float enemy_sprite_count{8.0f};

            Vector2 velocity{};
        
        private:
            bool alive{true};
    };

#endif
