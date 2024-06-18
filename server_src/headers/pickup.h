#ifndef PICKUP_H
#define PICKUP_H

#include "../../common_src/headers/Container.h"
#include "../../common_src/headers/sound_commands.h"

#include "objeto.h"

class Pickup: public Objeto {

protected:
    Queue<Container>& q;

public:
    Pickup(float x, float y, float width, float height, EntityType entity_type,
           AnimationType animation_type, Queue<Container>& q);

    virtual void colision(Objeto& o) override;
    virtual void colision(Personaje& p) override = 0;
    virtual void eliminar() override;
};

#endif
