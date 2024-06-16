#include "headers/zanahoria.h"

Zanahoria::Zanahoria(float x, float y, std::map<std::string, float>& config):
        Pickup(x, y, 3, 5, EntityType::CARROT, AnimationType::PICKUP),
        config(config),
        life(config["carrot_addlife"]) {}

void Zanahoria::colision(Personaje& p) {
    borrar = true;
    if (p.vida > 0) {  // Chequea que no este muerto
        p.vida += life;
    }

    if (p.vida > 100) {  // Chequea que no supere la vida maxima
        p.vida = config["player_life"];
    }

    std::cout << "Vida: " << p.vida << "\n";
}
