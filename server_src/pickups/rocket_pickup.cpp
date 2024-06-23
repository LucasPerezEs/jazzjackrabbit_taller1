#include "../headers/rocket_pickup.h"

RocketPickup::RocketPickup(float x, float y, std::map<std::string, float>& config,
                           Queue<Container>& q):
        Pickup(x, y, 1, 1, EntityType::ROCKET, AnimationType::PICKUP, q),
        add_ammo(config["rocket_pickup_addammo"]) {}

void RocketPickup::colision(Personaje& p) {
    borrar = true;
    p.add_ammo(EntityType::ROCKET, add_ammo);
    Container c(en_type, SoundType::PICKUP_SOUND, p.id);
    q.try_push(c);
}
