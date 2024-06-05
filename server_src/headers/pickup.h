#ifndef PICKUP_H
#define PICKUP_H

#include "objeto.h"

class Pickup: public Objeto {
public:
    Pickup(float x, float y, float width, float height, EntityType entity_type,
           AnimationType animation_type);

    virtual void colision(Objeto& o) override;
    virtual void colision(Personaje& p) override = 0;
    virtual void eliminar() override;
};

#endif
