#include "../headers/pickup.h"

#include <iostream>

#include "../headers/character.h"

Pickup::Pickup(float x, float y, float width, float height, EntityType entity_type,
               AnimationType animation_type, Queue<Container>& q):
        Object(x, y, width, height, entity_type, animation_type), q(q) {}

void Pickup::colision(Object& o) {
    if (check_colision(o)) {
        o.colision(*this);
    }
}

void Pickup::eliminar() { delete (this); }
