#include "../headers/poisoned_carrot.h"

PoisonedCarrot::PoisonedCarrot(float x, float y, std::map<std::string, float>& config,
                               Queue<Container>& q):
        Pickup(x, y, 2, 3, EntityType::INTOXICATED_CARROT, AnimationType::PICKUP, q),
        config(config),
        life(config["carrot_addlife"]) {}

void PoisonedCarrot::colision(Character& p) {
    borrar = true;

    p.colision(*this);
}
