#include "../headers/bullet_ammo.h"

BulletAmmo::BulletAmmo(float x, float y, std::map<std::string, float>& config, Queue<Container>& q):
        Pickup(x, y, 1, 1, EntityType::BULLET, AnimationType::PICKUP, q),
        add_ammo(config["ammo_addammo"]) {}

void BulletAmmo::colision(Character& p) {
    borrar = true;
    p.add_ammo(EntityType::BULLET, add_ammo);
    Container c(en_type, SoundType::PICKUP_SOUND, p.id);
    q.try_push(c);
}
