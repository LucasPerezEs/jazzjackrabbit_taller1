#include "personaje.h"
#include "enemigo.h"
#include <map>

Personaje::Personaje(int x, int y, int w, int h, int vida): Ente(x, y, w+x, h+y, vida) {
    direccion = 1;
}

void Personaje::mover(int movx, int movy) {
        if (movx > 0) {
            direccion = 1;
        } else {
            direccion = -1;
        }
        x += movx;
        width += movx;
        y += movy;
        height += movy;
    }
void Personaje::colision(Objeto &o) {
        if (this == &o) {
            return;
        }
        if (x < (o.width) && (width) > o.x && y < (o.height) && (height) > o.y) {
            o.colision(*this);
        }
    }
void Personaje::colision(Enemigo &e) {
        e.colision(*this);
    }
void Personaje::disparar(std::map<Objeto*, Objeto*>& objetos) {
        arma.disparar(objetos, x, width, y, height, direccion);
    }
