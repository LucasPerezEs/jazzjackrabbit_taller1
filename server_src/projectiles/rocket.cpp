#include "../headers/rocket.h"

Rocket::Rocket(float x, float y, int d, int shooter_id, std::map<std::string, float>& config):
        Projectile(x, y, d, shooter_id, EntityType::ROCKET, AnimationType::WALK,
                   config["rocket_speed"], config["rocket_damage"]) {}
