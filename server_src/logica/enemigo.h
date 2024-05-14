#ifndef ENEMIGO_H_
#define ENEMIGO_H_

#include "objeto.h"
#include <map>

class Enemigo: public Ente {
    protected:
    int daño;
    public:
    Enemigo(int x, int y, int w, int h, int vida);
    void mover(int movx, int movy);
    virtual void colision(Objeto &o);
    virtual void colision(Personaje &p);
    virtual void colision(Bala &b);
};


#endif