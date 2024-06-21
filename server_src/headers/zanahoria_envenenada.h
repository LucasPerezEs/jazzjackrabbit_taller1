#ifndef ZANAHORIA_ENVENENADA_H
#define ZANAHORIA_ENVENENADA_H

#include <iostream>
#include <map>
#include <string>

#include "../../common_src/headers/Container.h"
#include "../../common_src/headers/sound_commands.h"

#include "personaje.h"
#include "pickup.h"

class ZanahoriaEnvenenada: public Pickup {
private:
    std::map<std::string, float>& config;
    float life;

public:
    ZanahoriaEnvenenada(float x, float y, std::map<std::string, float>& config, Queue<Container>& q);

    virtual void colision(Personaje& p) override;
};



#endif  // ZANAHORIA_ENVENENADA_H
