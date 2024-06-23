#ifndef GHOST_H_
#define GHOST_H_

#include <map>
#include <string>
#include <unordered_map>

#include "../../common_src/headers/queue.h"

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

public:
    Ghost(float x, float y, std::map<std::string, float>& config);
    virtual void update(Mapa& m, ListaObjetos& objetos, Queue<Container>& q) override;
    virtual void update_vivo(ListaObjetos& objetos, Queue<Container>& q,
                             std::map<uint32_t, std::shared_ptr<Personaje>>& clientCharacters, std::shared_ptr<Ente> e) override;
};


#endif
