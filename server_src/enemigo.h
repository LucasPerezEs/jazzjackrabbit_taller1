#ifndef ENEMIGO_H_
#define ENEMIGO_H_

#include "objeto.h"
#include <map>

class Enemigo: public Ente {
    protected:
    int daño;
    public:
    Enemigo(float x, float y, float w, float h, int vida);
    virtual void colision(Objeto &o);
    virtual void colision(Personaje &p);
    virtual void colision(Bala &b);
};


#endif