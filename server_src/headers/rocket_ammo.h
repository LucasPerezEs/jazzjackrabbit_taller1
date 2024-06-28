#ifndef ROCKET_PICKUP_H
#define ROCKET_PICKUP_H

#include <iostream>
#include <map>
#include <string>

#include "../../common_src/headers/Container.h"
#include "../../common_src/headers/sound_commands.h"

#include "character.h"
#include "pickup.h"

class RocketAmmo: public Pickup {
private:
    int add_ammo;

public:
    RocketAmmo(float x, float y, std::map<std::string, float>& config, Queue<Container>& q);

    virtual void colision(Character& p) override;
};

#endif
