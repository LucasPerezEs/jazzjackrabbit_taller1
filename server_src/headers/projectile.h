#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <map>
#include <string>

#include "../../common_src/headers/queue.h"

#include "enemigo.h"
#include "lista_objetos.h"
#include "mapa.h"
#include "objeto.h"

class Personaje;

class Projectile: public Objeto {
protected:
    float vel;
    int shooter_id;
    int d;

public:
    int danio;
    Projectile(float x, float y, int d, int shooter_id, EntityType en_type, AnimationType an_type,
               int vel, int danio);
    virtual void colision(Objeto& o) override;
    virtual void colision(Enemigo& e) override;
    virtual void colision(Personaje& p) override;
    virtual void update(Mapa& m, ListaObjetos& objetos, Queue<Container>& q) override;
    virtual void eliminar() override;
    int get_shooter_id();
};

#endif
