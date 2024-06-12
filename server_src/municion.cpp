#include "headers/municion.h"

Municion::Municion(float x, float y, std::map<std::string, float>& config):
        Pickup(x, y, 2, 2, EntityType::BULLET, AnimationType::PICKUP),
        add_ammo(config["ammo_addammo"]) {}

void Municion::colision(Personaje& p) {
    borrar = true;
    p.municion += add_ammo;
    std::cout << "Municion: " << p.municion << "\n";
}
