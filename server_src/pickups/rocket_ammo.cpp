#include "../headers/rocket_ammo.h"

RocketAmmo::RocketAmmo(float x, float y, std::map<std::string, float>& config, Queue<Container>& q):
        Pickup(x, y, 1, 1, EntityType::ROCKET, AnimationType::PICKUP, q),
        add_ammo(config["rocket_pickup_addammo"]) {}

void RocketAmmo::colision(Character& p) {
    borrar = true;
    p.add_ammo(EntityType::ROCKET, add_ammo);
    Container c(en_type, SoundType::PICKUP_SOUND, p.id);
    q.try_push(c);
}
