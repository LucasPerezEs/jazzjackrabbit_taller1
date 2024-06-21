#include "../headers/zanahoria.h"

Zanahoria::Zanahoria(float x, float y, std::map<std::string, float>& config, Queue<Container>& q):
        Pickup(x, y, 2, 3, EntityType::INTOXICATED_CARROT, AnimationType::PICKUP, q),
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
