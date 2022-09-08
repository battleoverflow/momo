#include "raylib.h"

class Environment {
    public:
        Environment(Vector2 position, Texture2D texture_2);
        void render(Vector2 momo_pos);
        Rectangle get_collision_rec(Vector2 momo_pos);
    private:
        Texture2D texture{};
        Vector2 world_pos{};
        float env_scale{4.0f};
};