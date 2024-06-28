#ifndef ZANAHORIA_ENVENENADA_H
#define ZANAHORIA_ENVENENADA_H

#include <iostream>
#include <map>
#include <string>

#include "../../common_src/headers/Container.h"
#include "../../common_src/headers/sound_commands.h"

#include "character.h"
#include "pickup.h"

class PoisonedCarrot: public Pickup {
private:
    std::map<std::string, float>& config;
    float life;

public:
    PoisonedCarrot(float x, float y, std::map<std::string, float>& config, Queue<Container>& q);

    virtual void colision(Character& p) override;
};


#endif  // ZANAHORIA_ENVENENADA_H
