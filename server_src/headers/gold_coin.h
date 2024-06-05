#ifndef COIN_H
#define COIN_H

#include <iostream>

#include "personaje.h"
#include "pickup.h"

class Gold_Coin: public Pickup {
public:
    Gold_Coin(float x, float y);

    virtual void colision(Personaje& p) override;
};

#endif
