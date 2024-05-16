#include "headers/mapa.h"

Piso::Piso(float posx, float posy, float width,
           float height) {  // Lo llame piso pero tambien puede ser una pared
    x = posx;
    y = posy;  // hitbox
    w = width;
    h = height;
}

bool Piso::colision(float posx, float posy, float width, float height) {
    if (x < (width) && (w) > posx && y < (height) && (h) > posy) {
        return true;
    }
    return false;
}


Mapa::Mapa() {
    Piso* piso = new Piso(0, -1, 1000, 0);   // piso
    Piso* piso2 = new Piso(99, 0, 100, 50);  // pared derecha
    Piso* piso3 = new Piso(0, 0, 1, 50);     // pared izquierda
    Piso* piso4 = new Piso(20, 10, 35, 11);  // plataforma
    objetos.push_back(piso);
    objetos.push_back(piso2);
    objetos.push_back(piso3);
    objetos.push_back(piso4);
}

bool Mapa::CheckColision(
        float x, float y, float w,
        float h) {  // devuelve true si la hitbox que le paso por parametro colisiona con el mapa
    for (auto p: objetos) {
        if (p->colision(x, y, w, h)) {
            return true;
        }
    }
    return false;
}
