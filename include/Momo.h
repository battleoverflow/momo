#ifndef MOMO_H
    #define MOMO_H

    #pragma once

    #include <iostream>
    #include <stdio.h>
    #include <string.h>
    #include "include/BaseCharacter.h"

    #include "raylib.h"

    class Momo : public BaseCharacter {
        public:
            Momo(int winWidth, int winHeight);
            virtual void tick(float delta_time) override;
            virtual Vector2 get_screen_pos() override;
            float get_health() const { return health; }
            void take_damage(float damage);
        
        private:
            int window_width{};
            int window_height{};
            float health{100.0f};
    };

#endif