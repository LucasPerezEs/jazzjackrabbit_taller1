#ifndef ENEMIGO_H_
#define ENEMIGO_H_

#include <map>

#include "objeto.h"

class Enemigo: public Ente {
protected:
    int danio;

public:
    Enemigo(float x, float y, float w, float h, int vida);
    virtual void colision(Objeto& o) override;
    virtual void colision(Personaje& p) override;
    virtual void colision(Bala& b) override;
};


#endif
