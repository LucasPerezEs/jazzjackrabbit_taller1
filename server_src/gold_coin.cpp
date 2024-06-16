#include "headers/gold_coin.h"

Gold_Coin::Gold_Coin(float x, float y, std::map<std::string, float>& config):
        Pickup(x, y, 3, 3, EntityType::GOLD_COIN, AnimationType::PICKUP),
        score(config["goldcoin_addscore"]) {}

void Gold_Coin::colision(Personaje& p) {
    borrar = true;
    p.add_score(score);
}
