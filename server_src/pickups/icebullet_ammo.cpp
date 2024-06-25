#include "../headers/icebullet_ammo.h"

IceBulletAmmo::IceBulletAmmo(float x, float y, std::map<std::string, float>& config,
                             Queue<Container>& q):
        Pickup(x, y, 1, 1, EntityType::ICE_BULLET, AnimationType::PICKUP, q),
        add_ammo(config["icebullet_addammo"]) {}

void IceBulletAmmo::colision(Personaje& p) {
    borrar = true;
    p.add_ammo(EntityType::ICE_BULLET, add_ammo);
    Container c(en_type, SoundType::PICKUP_SOUND, p.id);
    q.try_push(c);
}
