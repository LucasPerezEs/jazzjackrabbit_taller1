#include "headers/enemigo.h"

#include <iostream>


Enemigo::Enemigo(float x, float y, float w, float h, float life, float speed, float damage,
                 EntityType en_type, AnimationType an_type):
        Ente(x, y, w, h, life, en_type, an_type), damage(damage), speed(speed) {
    direccion = 1;
    contador = 0;
}

void Enemigo::colision(Objeto& o) {
    if (check_colision(o)) {
        o.colision(*this);
    }
}
void Enemigo::colision(Personaje& p) {
    if (p.has_special_action_active()) {
        this->RecibirDanio(p.danio_ataque_especial);
    } else {
        p.RecibirDanio(damage);
    }
}

void Enemigo::colision(Bala& b) {
    b.borrar = true;
    RecibirDanio(b.danio);
}
