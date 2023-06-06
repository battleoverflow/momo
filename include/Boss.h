/*
    Project: Momo's Quest (https://github.com/azazelm3dj3d/momo)
    Author: azazelm3dj3d (https://github.com/azazelm3dj3d)
    License: MIT
*/

#ifndef BOSS_H
    #define BOSS_H

    #include "raylib.h"
    #include "include/BaseCharacter.h"
    #include "include/Momo.h"

    class Boss : public BaseCharacter {
        public:
            Boss(Vector2 pos, Texture2D idle_tex, Texture2D run_tex, Texture2D death_tex, Texture2D attack_tex);
            virtual void tick(float delta_time) override;
            void set_target(Momo* momo) { target = momo; }
            void take_damage(float damage);
            float get_health() const { return health; }
            virtual Vector2 get_screen_pos() override;
        private:
            Momo* target;
            float dps{10.0f};
            float radius{25.0f};
            float health{100.0f};
    };

#endif
