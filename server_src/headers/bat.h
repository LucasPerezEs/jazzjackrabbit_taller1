#ifndef BAT_H_
#define BAT_H_

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

class Bat: public Enemigo {
protected:
    float lim_y_sup;
    float lim_y_inf;

public:
    Bat(float x, float y, std::map<std::string, float>& config);
    virtual void update(Mapa& m, ListaObjetos& objetos, Queue<Container>& q) override;
    virtual void update_vivo(ListaObjetos& objetos, Queue<Container>& q) override;
};

#endif
