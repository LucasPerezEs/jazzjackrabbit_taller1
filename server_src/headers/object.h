#ifndef OBJETO_H_
#define OBJETO_H_

#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

#include "../../common_src/headers/Container.h"
#include "../../common_src/headers/entity_commands.h"
#include "../../common_src/headers/queue.h"


class Enemy;
class Character;
class Projectile;
class Banana;
class Map;
class BulletAmmo;
class ObjectList;
class Pickup;
class PoisonedCarrot;

class Object {
public:
    int id;
    float x;  // estos atributos es la hitbox del objeto
    float y;
    float width;
    float height;
    bool borrar;            // borrar se usa para borrar del map de colisiones al objeto
    EntityType en_type;     // Identifica al objeto con un tipo (ej. Bala, Jazz, Lori, etc)
    AnimationType an_type;  // Tipo de animacion inicial del objeto.

public:
    Object(float x, float y, float w, float h, EntityType en_type, AnimationType an_type);

    virtual void update(Map& m, ObjectList& objetos, Queue<Container>& q);
    virtual void eliminar();
    bool check_colision(Object& o);
    virtual void colision(Object& o) = 0;
    virtual void colision(Pickup& o);
    virtual void colision(Character& o);
    virtual void colision(Enemy& o);
    virtual void colision(Projectile& o);
    virtual void colision(Banana& o);
    virtual void colision(BulletAmmo& m);
    virtual void colision(PoisonedCarrot& ze);
    virtual ~Object();
};

class Entity: public Object {  // objetos con vida
protected:
    bool killed;
    std::chrono::system_clock::time_point last_killed;
    int direccion;          // para donde se mueven
    unsigned int contador;  // se usa para llevar el tiempo de muerte y eso
public:
    int vida;
    int spawn;
    Entity(float x, float y, float w, float h, int vida, EntityType en_type, AnimationType an_type);
    void RecibirDanio(int d);
    bool vivo();
    virtual void update_vivo(ObjectList& objetos, Queue<Container>& q,
                             std::map<uint32_t, std::shared_ptr<Character>>& clientCharacters,
                             std::shared_ptr<Entity> e);
};


#endif
