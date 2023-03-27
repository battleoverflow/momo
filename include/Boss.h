#include "raylib.h"
#include "include/BaseCharacter.h"
#include "include/Momo.h"

class Boss : public BaseCharacter {
    public:
        Boss(Vector2 pos, Texture2D idle_tex, Texture2D run_tex, Texture2D death_tex);
        virtual void tick(float delta_time) override;
        void set_target(Momo* momo) { target = momo; }
        virtual Vector2 get_screen_pos() override;
    private:
        Momo* target;
        float dps{10.0f};
};