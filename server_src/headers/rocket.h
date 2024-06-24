#ifndef ROCKET_H
#define ROCKET_H

#include <map>
#include <string>

#include "projectile.h"

class Rocket: public Projectile {
private:
    std::chrono::system_clock::time_point tiempo;
    int wait_explosion;
    bool exploded;

public:
    Rocket(float x, float y, int d, int shooter_id, std::map<std::string, float>& config);
    virtual void colision(Objeto& o) override;
    virtual void colision(Enemigo& e) override;
    virtual void colision(Personaje& p) override;
    virtual void update(Mapa& m, ListaObjetos& objetos, Queue<Container>& q) override;
};


#endif
