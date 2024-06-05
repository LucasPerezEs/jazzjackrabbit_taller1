#include "headers/player.h"

Player::Player(int id, float x, float y, float width, float height, int direccion,
               AnimationType an_type, Animation* an, EntityType entity_type, int vida, int municion,
               int score):
        Entity(id, x, y, width, height, direccion, an_type, an, entity_type),
        vida(vida),
        municion(municion),
        score(score) {}

void Player::update_player_stats(float new_x, float new_y, float new_width, float new_height,
                                 int new_direccion, int new_vida, int new_municion, int new_score) {
    update_stats(new_x, new_y, new_width, new_height, new_direccion);
    this->vida = new_vida;
    this->municion = new_municion;
    this->score = new_score;
}
