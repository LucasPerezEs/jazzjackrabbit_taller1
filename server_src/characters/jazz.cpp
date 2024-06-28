#include "../headers/jazz.h"

Jazz::Jazz(float x, float y, std::map<std::string, float>& config, Queue<Container>& q,
           // cppcheck-suppress passedByValue
           std::string name):
        Character(x, y, 2, 4, EntityType::JAZZ, AnimationType::SHOOT_IDLE, config, q, name) {}

void Jazz::special_action() {
    if (!special_action_active) {
        special_action_active = true;
        movingleft = false;
        movingright = false;
        vely = jump_speed + 1;
        jumping = true;
        an_type = AnimationType::SPECIAL_ACTION;
        tiempo = std::chrono::system_clock::now();
    }
}

void Jazz::check_special_action(bool col_x, bool col_y) {
    if (col_y) {
        special_action_active = false;
    }
}
