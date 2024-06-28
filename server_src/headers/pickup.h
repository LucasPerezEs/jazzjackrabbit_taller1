#ifndef PICKUP_H
#define PICKUP_H

#include "../../common_src/headers/Container.h"
#include "../../common_src/headers/sound_commands.h"

#include "object.h"

class Pickup: public Object {

protected:
    Queue<Container>& q;

public:
    Pickup(float x, float y, float width, float height, EntityType entity_type,
           AnimationType animation_type, Queue<Container>& q);

    virtual void colision(Object& o) override;
    virtual void colision(Character& p) override = 0;
    virtual void eliminar() override;
};

#endif
