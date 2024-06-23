#ifndef OBJETO_H_
#define OBJETO_H_

#include <map>
#include <unordered_map>
#include <vector>

#include "../../common_src/headers/Container.h"
#include "../../common_src/headers/entity_commands.h"
#include "../../common_src/headers/queue.h"


class Enemigo;
class Personaje;
class Projectile;
class Banana;
class Mapa;
class Municion;
class ListaObjetos;
class Pickup;
class ZanahoriaEnvenenada;

class Objeto {
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
    Objeto(float x, float y, float w, float h, EntityType en_type, AnimationType an_type);

    virtual void update(Mapa& m, ListaObjetos& objetos, Queue<Container>& q);
    virtual void eliminar();
    bool check_colision(Objeto& o);
    virtual void colision(Objeto& o) = 0;
    virtual void colision(Pickup& o);
    virtual void colision(Personaje& o);
    virtual void colision(Enemigo& o);
    virtual void colision(Projectile& o);
    virtual void colision(Banana& o);
    virtual void colision(Municion& m);
    virtual void colision(ZanahoriaEnvenenada& ze);
    virtual ~Objeto();
};

class Ente: public Objeto {  // objetos con vida
protected:
    int direccion;          // para donde se mueven
    unsigned int contador;  // se usa para llevar el tiempo de muerte y eso
public:
    int vida;

    Ente(float x, float y, float w, float h, int vida, EntityType en_type, AnimationType an_type);
    void RecibirDanio(int d);
    bool vivo();
    virtual void update_vivo(ListaObjetos& objetos, Queue<Container>& q,
                             std::unordered_map<uint32_t, Personaje*>& clientCharacters);
};


#endif
