#ifndef MUNICION_H
#define MUNICION_H

#include <iostream>

#include "personaje.h"
#include "pickup.h"

class Municion: public Pickup {
public:
    Municion(float x, float y);

    virtual void colision(Personaje& p) override;
};

#endif
