#include "enemigo.h"
#include "personaje.h"
#include <iostream>


Enemigo::Enemigo(float x, float y, float w, float h, int vida): Ente(x, y, w+x, h+y, vida) {
        daño = 10;
}

void Enemigo::colision(Objeto &o) {
        if (this == &o) {
            return;
        }
        if (x < (o.width) && (width) > o.x && y < (o.height) && (height) > o.y) {
            o.colision(*this);
        }
}
void Enemigo::colision(Personaje &p) {
        p.RecibirDaño(daño);
        //std::cout << "Enemigo atacó con " << daño << "de daño\n";
        //std::cout << "Vida restante del personaje: " << p.vida << "\n";
}
void Enemigo::colision(Bala &b) {
        //std::cout << "bala x: (" << b.x << "," << b.width << ")\n";
        //std::cout << "Bala colisiona con enemigo\n";
        b.borrar = true;
        RecibirDaño(b.daño);
}