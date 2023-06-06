/*
    Project: Momo's Quest (https://github.com/azazelm3dj3d/momo)
    Author: azazelm3dj3d (https://github.com/azazelm3dj3d)
    License: MIT
*/

#ifndef ENVIRONMENT_H
    #define ENVIRONMENT_H

    #include "raylib.h"

    class Environment {
        public:
            Environment(Vector2 position, Texture2D tex);
            void render(Vector2 momo_pos);
            Rectangle get_collision_rec(Vector2 momo_pos);
        private:
            Texture2D texture{};
            Vector2 world_pos{};
            float scale{4.0f};
    };

#endif
