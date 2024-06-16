#ifndef COIN_H
#define COIN_H

#include <iostream>
#include <map>
#include <string>

#include "personaje.h"
#include "pickup.h"

class Gold_Coin: public Pickup {
private:
    float score;

public:
    Gold_Coin(float x, float y, std::map<std::string, float>& config);

    virtual void colision(Personaje& p) override;
};

#endif
