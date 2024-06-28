#include "headers/player.h"

Player::Player(int id, float x, float y, float width, float height, int direccion,
               AnimationType an_type, Animation* an, EntityType entity_type, int vida,
               // cppcheck-suppress passedByValue
               AmmoData municion, int score, std::string name):
        Entity(id, x, y, width, height, direccion, an_type, an, entity_type),
        vida(vida),
        municion(municion),
        score(score),
        name(name),
        dead(false) {}

void Player::update_player_stats(float new_x, float new_y, float new_width, float new_height,
                                 int new_direccion, int new_vida, AmmoData new_municion,
                                 // cppcheck-suppress passedByValue
                                 int new_score, std::string name) {
    update_stats(new_x, new_y, new_width, new_height, new_direccion);
    this->vida = new_vida;
    this->municion = new_municion;
    this->score = new_score;
    this->name = name;
}

int Player::get_vida() { return this->vida; }

AmmoData Player::get_municion() { return this->municion; }

int Player::get_score() { return this->score; }

std::string Player::get_name() { return this->name; }

bool Player::get_dead() {
    return dead;
}

void Player::set_dead(bool d) {
    dead = d;
}