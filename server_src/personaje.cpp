#include "personaje.h"
#include "enemigo.h"
#include <map>
#include <iostream>

Personaje::Personaje(float x, float y, float w, float h, int vida): Ente(x, y, w+x, h+y, vida) {
    velx = 1;
    vely = 0;
    direccion = 1;
    jumping = false;
}

void Personaje::moveRigth() {
    moving = true;
    direccion = 1;

}
void Personaje::moveLeft() {
    moving = true;
    direccion = -1;
}
void Personaje::stopMoving() {
    moving = false;
}

void Personaje::jump() {
    if (!jumping) { // Esto es para evitar que se pueda spamear el jump y volar
        vely = 2;
        jumping = true;
    }
}

void Personaje::update(Mapa& m) {
    float auxx = x;
    float auxy = y;       // se guarda la posicion actual
    float auxw = width;
    float auxh = height;
    if (moving) {  // mientras se este apretando una tecla de mover el jugador
        x += velx*direccion; // se actualiza la posicin en x
        width += velx*direccion;
        if (m.CheckColision(x, auxy, width, auxh)) { // si colisiona con la pos x actualizada 
            x = auxx;                                // se pone la pos x anterior
            width = auxw;                            // lo mismo con la pos y
        }
    }
    y += vely;
    height += vely;
    vely -= 0.2; // esto es la aceleracion de la gravedad, se tiene que poner un limite de vely
    if (m.CheckColision(auxx, y, auxw, height)) {
        jumping = false; // esta en el piso se puede saltar
        vely = 0;
        y = auxy;
        height = auxh;
    }
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
