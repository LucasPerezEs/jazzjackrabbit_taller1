#include "../headers/gem.h"

Gem::Gem(float x, float y, std::map<std::string, float>& config, Queue<Container>& q):
        Pickup(x, y, 1.5, 1.5, EntityType::GEM, AnimationType::PICKUP, q),
        score(config["gem_addscore"]) {}

void Gem::colision(Personaje& p) {
    borrar = true;
    p.add_score(score);

    Container c(EntityType::GEM, SoundType::PICKUP_SOUND, p.id);
    q.try_push(c);
}
