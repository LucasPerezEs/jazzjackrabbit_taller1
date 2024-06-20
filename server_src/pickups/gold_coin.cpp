#include "../headers/gold_coin.h"

Gold_Coin::Gold_Coin(float x, float y, std::map<std::string, float>& config, Queue<Container>& q):
        Pickup(x, y, 3, 3, EntityType::GOLD_COIN, AnimationType::PICKUP, q),
        score(config["goldcoin_addscore"]) {}

void Gold_Coin::colision(Personaje& p) {
    borrar = true;
    p.add_score(score);

    Container c(EntityType::GOLD_COIN, SoundType::PICKUP_SOUND, p.id);
    q.try_push(c);
}
