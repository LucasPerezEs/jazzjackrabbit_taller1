#ifndef ENEMIGO_H_
#define ENEMIGO_H_

#include <map>
#include <string>

#include "../../common_src/headers/queue.h"

#include "contenedor.h"
#include "gold_coin.h"
#include "lista_objetos.h"
#include "municion.h"
#include "objeto.h"
#include "personaje.h"
#include "zanahoria.h"

class ListaObjetos;

class Enemigo: public Ente {
protected:
    int damage;
    float speed;

public:
    Enemigo(float x, float y, float w, float h, float vida, float speed, float damage,
            EntityType en_type, AnimationType an_type);
    virtual void colision(Objeto& o) override;
    virtual void colision(Personaje& p) override;
    virtual void colision(Bala& b) override;
    virtual void update(Mapa& m, ListaObjetos& objetos, Queue<Contenedor>& q) override = 0;
    virtual void update_vivo(ListaObjetos& objetos, Queue<Contenedor>& q) override = 0;
    virtual Pickup* drop_item() = 0;
};


#endif
