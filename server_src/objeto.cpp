#include <iostream>
#include <vector>
#include "objeto.h"
#include "mapa.h"


Objeto::Objeto(float x, float y, float w, float h): x(x), y(y), width(w), height(h), borrar(false) {}

Ente::Ente(float x, float y, float w, float h, int vida): Objeto(x, y, w, h), vida(vida) { //para la direccion 1 es a la derecha y -1 a la izquierda
    int direccion = 1;
}
                                              // hitbox
Bala::Bala(float x, float y, int d): Objeto(x, y, x+1, y+1) { // se le pasa la direccion a la que va a salir la bala por parametro
    vel = 1*d;
    daño = 10;
}


void Objeto::update(Mapa &m) {};
void Objeto::colision(Personaje &o) {}; // Double dispatch
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
void Bala::update(Mapa &mapa) { // actualiza la posicion, si choca con el mapa se tiene que borrar
    x += vel;
    width += vel;
    if (mapa.CheckColision(x, y, width, height)) {
        this->borrar = true;
    }
}


void Arma::disparar(std::map<Objeto*, Objeto*>& objetos, float x, float w, float y, float h, int d) {
    int aux;
    if (d == 1) {   // Si se dispara mirando a la derecha la bala sale desde la derecha del objeto
        aux = w;    // Si se dispara mirando a la izquierda sale a la izquierda
    } else {
        aux = x;
    }
    Bala *b = new Bala(aux, (y+h)/2, d);
    objetos[b] = b; // Se agrega al map de colisiones
}
