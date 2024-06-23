#include "../headers/bullet.h"

Bullet::Bullet(float x, float y, int d, int shooter_id, std::map<std::string, float>& config):
        Projectile(x, y, d, shooter_id, EntityType::BULLET, AnimationType::WALK,
                   config["bullet_speed"], config["bullet_damage"]) {}
