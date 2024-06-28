#include "../headers/carrot.h"

Carrot::Carrot(float x, float y, std::map<std::string, float>& config, Queue<Container>& q):
        Pickup(x, y, 2, 3, EntityType::CARROT, AnimationType::PICKUP, q),
        config(config),
        life(config["carrot_addlife"]) {}

void Carrot::colision(Character& p) {
    borrar = true;
    if (p.vida > 0) {
        p.vida += life;
    }

    if (p.vida > 100) {
        p.vida = config["player_life"];
    }
}
