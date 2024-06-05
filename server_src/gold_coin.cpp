#include "headers/gold_coin.h"

Gold_Coin::Gold_Coin(float x, float y):
        Pickup(x, y, x + 3, y + 3, EntityType::GOLD_COIN, AnimationType::PICKUP) {}

void Gold_Coin::colision(Personaje& p) {
    borrar = true;
    p.add_score(10);
}
