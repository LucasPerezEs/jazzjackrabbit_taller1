#include "../headers/icebullet.h"

IceBullet::IceBullet(float x, float y, int d, int shooter_id, std::map<std::string, float>& config):
        Projectile(x, y, d, shooter_id, EntityType::ICE_BULLET, AnimationType::SHOOT,
                   config["ice_bullet_speed"], config["ice_bullet_damage"]) {}
