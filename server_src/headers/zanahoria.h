#ifndef ZANAHORIA_H
#define ZANAHORIA_H

#include <iostream>

#include "personaje.h"
#include "pickup.h"

class Zanahoria: public Pickup {
public:
    Zanahoria(float x, float y);

    virtual void colision(Personaje& p) override;
};

#endif
