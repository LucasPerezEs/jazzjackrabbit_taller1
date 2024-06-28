#ifndef ZANAHORIA_H
#define ZANAHORIA_H

#include <iostream>
#include <map>
#include <string>

#include "../../common_src/headers/Container.h"
#include "../../common_src/headers/sound_commands.h"

#include "character.h"
#include "pickup.h"

class Carrot: public Pickup {
private:
    std::map<std::string, float>& config;


public:
    float life;
    Carrot(float x, float y, std::map<std::string, float>& config, Queue<Container>& q);

    virtual void colision(Character& p) override;
};

#endif
