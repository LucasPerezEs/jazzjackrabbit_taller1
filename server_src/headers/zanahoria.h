#ifndef ZANAHORIA_H
#define ZANAHORIA_H

#include <iostream>
#include <map>
#include <string>

#include "../../common_src/headers/Container.h"
#include "../../common_src/headers/sound_commands.h"

#include "personaje.h"
#include "pickup.h"

class Zanahoria: public Pickup {
private:
    std::map<std::string, float>& config;
    

public:
    float life;
    Zanahoria(float x, float y, std::map<std::string, float>& config, Queue<Container>& q);

    virtual void colision(Personaje& p) override;
};

#endif
