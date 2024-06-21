#include "../headers/zanahoria_envenenada.h"

ZanahoriaEnvenenada::ZanahoriaEnvenenada(float x, float y, std::map<std::string, float>& config,
                                         Queue<Container>& q):
        Pickup(x, y, 3, 5, EntityType::INTOXICATED_CARROT, AnimationType::PICKUP, q),
        config(config),
        life(config["carrot_addlife"]) {}

void ZanahoriaEnvenenada::colision(Personaje& p) {
    borrar = true;

    p.colision(*this);

}
