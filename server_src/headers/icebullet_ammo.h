#ifndef ICEBULLET_AMMO_H
#define ICEBULLET_AMMO_H

#include <iostream>
#include <map>
#include <string>

#include "../../common_src/headers/Container.h"
#include "../../common_src/headers/sound_commands.h"

#include "character.h"
#include "pickup.h"

class IceBulletAmmo: public Pickup {
private:
    float add_ammo;

public:
    IceBulletAmmo(float x, float y, std::map<std::string, float>& config, Queue<Container>& q);

    virtual void colision(Character& p) override;
};

#endif
