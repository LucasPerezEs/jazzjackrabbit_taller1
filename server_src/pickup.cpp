#include "headers/pickup.h"

#include <iostream>

#include "headers/personaje.h"

Pickup::Pickup(float x, float y, float width, float height, EntityType entity_type,
               AnimationType animation_type):
        Objeto(x, y, width, height, entity_type, animation_type) {}

void Pickup::colision(Objeto& o) {
    if (this == &o) {
        return;
    }
    if (x < (o.width) && (width) > o.x && y < (o.height) && (height) > o.y) {
        o.colision(*this);
    }
}

void Pickup::eliminar() { delete (this); }
