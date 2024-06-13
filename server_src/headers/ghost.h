#ifndef GHOST_H_
#define GHOST_H_

#include <map>
#include <string>

#include "../../common_src/headers/queue.h"

#include "contenedor.h"
#include "enemigo.h"
#include "gold_coin.h"
#include "lista_objetos.h"
#include "municion.h"
#include "objeto.h"
#include "personaje.h"
#include "zanahoria.h"

class ListaObjetos;

class Ghost: public Enemigo {
protected:
    float lim_x_izq;
    float lim_x_der;
    float lim_y;
    std::map<std::string, float>& config;

public:
    Ghost(float x, float y, std::map<std::string, float>& config);
    virtual void update(Mapa& m, ListaObjetos& objetos, Queue<Contenedor>& q) override;
    virtual void update_vivo(ListaObjetos& objetos, Queue<Contenedor>& q) override;
    virtual Pickup* drop_item() override;
};


#endif