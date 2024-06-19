#ifndef MUNICION_H
#define MUNICION_H

#include <iostream>
#include <map>
#include <string>

#include "../../common_src/headers/Container.h"
#include "../../common_src/headers/sound_commands.h"

#include "personaje.h"
#include "pickup.h"

class Municion: public Pickup {
private:
    int add_ammo;

public:
    Municion(float x, float y, std::map<std::string, float>& config, Queue<Container>& q);

    virtual void colision(Personaje& p) override;
};

#endif
