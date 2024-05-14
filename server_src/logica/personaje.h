#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <vector>
#include "objeto.h"

class Personaje: public Ente {
    protected:
    int velx;
    int vely;
    Arma arma;
    
    public:
    Personaje(int x, int y, int w, int h, int vida);
    virtual void colision(Objeto &o);
    virtual void colision(Enemigo &e);
    void disparar(std::map<Objeto*, Objeto*>& objetos);
    virtual void mover(int movx, int movy);
};

#endif