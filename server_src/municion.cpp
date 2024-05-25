#include "headers/municion.h"

#include <iostream>

#include "headers/personaje.h"

Municion::Municion(float x, float y): Objeto(x, y, x + 1, y + 1) {}

void Municion::colision(Objeto& o) {
    if (this == &o) {
        return;
    }
    if (x < (o.width) && (width) > o.x && y < (o.height) && (height) > o.y) {
        o.colision(*this);
    }
}

void Municion::colision(Personaje& p) {
    borrar = true;
    p.municion++;
    std::cout << "Municion: " << p.municion << "\n";
}

void Municion::eliminar() { delete (this); }
