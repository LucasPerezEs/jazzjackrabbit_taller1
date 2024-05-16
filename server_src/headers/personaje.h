#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <map>
#include <vector>

#include "mapa.h"
#include "objeto.h"

class Personaje: public Ente {
protected:
    bool moving;
    bool jumping;
    float velx;
    float vely;
    Arma arma;

public:
    Personaje(float x, float y, float w, float h, int vida);
    virtual void colision(Objeto& o) override;
    virtual void colision(Enemigo& e) override;
    void disparar(std::map<Objeto*, Objeto*>& objetos);
    void moveRigth();
    void moveLeft();
    void stopMoving();
    void jump();
    virtual void update(Mapa& m) override;
};

#endif
