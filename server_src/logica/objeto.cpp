#include <iostream>
#include <vector>
#include "objeto.h"


Objeto::Objeto(int x, int y, int w, int h): x(x), y(y), width(w), height(h), borrar(false) {}

Ente::Ente(int x, int y, int w, int h, int vida): Objeto(x, y, w, h), vida(vida) {
    int direccion = 1;
}

Bala::Bala(int x, int y, int d): Objeto(x, y, x+1, y+1) {
    vel = 1*d;
    daño = 10;
}


void Objeto::avanzar() {};

void Objeto::colision(Personaje &o) {};
void Objeto::colision(Enemigo &o) {};
void Objeto::colision(Bala &o) {};


void Ente::RecibirDaño(int d) {
    vida -= d;
}

bool Ente::vivo() {
    return vida > 0;
}


void Bala::colision(Objeto &o){
    if (this == &o) {
        return;
    }
    if (x < (o.width) && (width) > o.x && y < (o.height) && (height) > o.y) {
        o.colision(*this);
    }
}
void Bala::avanzar(){
    x += vel;
    width += vel;
}


void Arma::disparar(std::map<Objeto*, Objeto*>& objetos, int x, int w, int y, int h, int d) {
    int aux;
    if (d == 1) {
        aux = w;
    } else {
        aux = x;
    }
    Bala *b = new Bala(aux, (y+h)/2, d);
    objetos[b] = b;
}
