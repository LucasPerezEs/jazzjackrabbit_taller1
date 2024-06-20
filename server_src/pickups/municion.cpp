#include "../headers/municion.h"

Municion::Municion(float x, float y, std::map<std::string, float>& config, Queue<Container>& q):
        Pickup(x, y, 2, 2, EntityType::BULLET, AnimationType::PICKUP, q),
        add_ammo(config["ammo_addammo"]) {}

void Municion::colision(Personaje& p) {
    borrar = true;
    p.municion += add_ammo;
    Container c(en_type, SoundType::PICKUP_SOUND, p.id);
    q.try_push(c);
    std::cout << "Municion: " << p.municion << "\n";
}
