#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <map>
#include <string>

#include "../../common_src/headers/queue.h"

#include "enemy.h"
#include "map.h"
#include "object.h"
#include "object_list.h"

class Personaje;

class Projectile: public Object {
protected:
    float vel;
    int shooter_id;
    int d;

public:
    int danio;
    Projectile(float x, float y, int d, int shooter_id, EntityType en_type, AnimationType an_type,
               int vel, int danio);
    virtual void colision(Object& o) override;
    virtual void colision(Enemy& e) override;
    virtual void colision(Character& p) override;
    virtual void update(Map& m, ObjectList& objetos, Queue<Container>& q) override;
    virtual void eliminar() override;
    int get_shooter_id();
};

#endif
