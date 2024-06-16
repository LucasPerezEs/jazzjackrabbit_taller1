#ifndef ZANAHORIA_H
#define ZANAHORIA_H

#include <iostream>
#include <map>
#include <string>

#include "personaje.h"
#include "pickup.h"

class Zanahoria: public Pickup {
private:
    std::map<std::string, float>& config;
    float life;

public:
    Zanahoria(float x, float y, std::map<std::string, float>& config);

    virtual void colision(Personaje& p) override;
};

#endif
