#include "headers/zanahoria.h"

Zanahoria::Zanahoria(float x, float y):
        Pickup(x, y, x + 3, y + 5, EntityType::CARROT, AnimationType::PICKUP) {}

void Zanahoria::colision(Personaje& p) {
    borrar = true;
    if (p.vida > 0) {  // Chequea que no este muerto
        p.vida += 10;
    }

    if (p.vida > 100) {  // Chequea que no supere la vida maxima
        p.vida = 100;
    }

    std::cout << "Vida: " << p.vida << "\n";
}
