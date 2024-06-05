#include "headers/municion.h"

Municion::Municion(float x, float y):
        Pickup(x, y, x + 2, y + 2, EntityType::BULLET, AnimationType::PICKUP) {}

void Municion::colision(Personaje& p) {
    borrar = true;
    p.municion++;
    std::cout << "Municion: " << p.municion << "\n";
}
