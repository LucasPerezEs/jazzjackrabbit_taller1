#include "headers/lori.h"

Lori::Lori(float x, float y, std::map<std::string, float>& config):
        Personaje(x, y, 2, 4, EntityType::LORI, AnimationType::SHOOT_IDLE, config) {}

void Lori::special_action() {
    if (!special_action_active) {
        special_action_active = true;
        movingleft = false;
        movingright = false;  //
        vely = jump_speed - 0.25;
        jumping = true;
        an_type = AnimationType::SPECIAL_ACTION;
        tiempo = std::chrono::system_clock::now();
    }
}