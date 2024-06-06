#ifndef PLAYER_H
#define PLAYER_H


#include <string>

#include <SDL2/SDL.h>

#include "../../common_src/headers/entity_commands.h"

#include "Animation.h"
#include "entity.h"

class Player: public Entity {
private:
    int vida;
    int municion;
    int score;

public:
    Player(int id, float x, float y, float width, float height, int direccion,
           AnimationType an_type, Animation* an, EntityType entity_type, int vida, int municion,
           int score);

    void update_player_stats(float x, float y, float width, float height, int direccion, int vida,
                             int municion, int score);

    int get_vida();
    int get_municion();
    int get_score();

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    Player(Player&&) = default;
    Player& operator=(Player&&) = default;
};

#endif
