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