#ifndef COIN_H
#define COIN_H

#include <iostream>
#include <map>
#include <string>

#include "../../common_src/headers/Container.h"
#include "../../common_src/headers/sound_commands.h"

#include "personaje.h"
#include "pickup.h"

class Gold_Coin: public Pickup {
private:
    float score;

public:
    Gold_Coin(float x, float y, std::map<std::string, float>& config, Queue<Container>& q);

    virtual void colision(Personaje& p) override;
};

#endif
