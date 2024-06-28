#ifndef PLAYER_H
#define PLAYER_H


#include <string>

#include <SDL2/SDL.h>

#include "../../common_src/headers/entity_commands.h"
#include "../../common_src/headers/protocol.h"

#include "Animation.h"
#include "entity.h"

class Player: public Entity {
private:
    int vida;
    AmmoData municion;
    int score;
    std::string name;
    bool dead;

public:
    Player(int id, float x, float y, float width, float height, int direccion,
           AnimationType an_type, Animation* an, EntityType entity_type, int vida,
           AmmoData municion, int score, std::string name);

    void update_player_stats(float x, float y, float width, float height, int direccion, int vida,
                             AmmoData municion, int score, std::string name);

    int get_vida();
    AmmoData get_municion();
    int get_score();
    std::string get_name();
    bool get_dead();
    void set_dead(bool d);

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    Player(Player&&) = default;
    Player& operator=(Player&&) = default;
};

#endif
