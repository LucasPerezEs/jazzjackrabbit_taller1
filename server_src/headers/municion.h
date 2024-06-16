#ifndef MUNICION_H
#define MUNICION_H

#include <iostream>
#include <map>
#include <string>

#include "personaje.h"
#include "pickup.h"

class Municion: public Pickup {
private:
    int add_ammo;

public:
    Municion(float x, float y, std::map<std::string, float>& config);

    virtual void colision(Personaje& p) override;
};

#endif
