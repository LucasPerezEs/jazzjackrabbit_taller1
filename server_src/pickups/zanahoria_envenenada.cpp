#include "../headers/zanahoria_envenenada.h"

ZanahoriaEnvenenada::ZanahoriaEnvenenada(float x, float y, std::map<std::string, float>& config,
                                         Queue<Container>& q):
        Pickup(x, y, 3, 5, EntityType::CARROT, AnimationType::PICKUP, q),
        config(config),
        life(config["carrot_addlife"]) {}

void ZanahoriaEnvenenada::colision(Personaje& p) {
    borrar = true;
    if (p.vida > 0) {
        p.vida += life;
    }

    if (p.vida > 100) {
        p.vida = config["player_life"];
    }

    std::cout << "Vida: " << p.vida << "\n";

    p.colision(*this);

}
