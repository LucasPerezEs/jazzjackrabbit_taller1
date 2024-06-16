#ifndef MONKEY_H_
#define MONKEY_H_

#include <map>
#include <string>

#include "../../common_src/headers/queue.h"

#include "banana.h"
#include "contenedor.h"
#include "enemigo.h"
#include "gold_coin.h"
#include "lista_objetos.h"
#include "municion.h"
#include "objeto.h"
#include "personaje.h"
#include "zanahoria.h"

class ListaObjetos;

class Monkey: public Enemigo {
protected:
    int wait_idle;
    int wait_throw;
    bool throwing_banana;
    std::chrono::system_clock::time_point tiempo;

public:
    Monkey(float x, float y, std::map<std::string, float>& config);
    virtual void update(Mapa& m, ListaObjetos& objetos, Queue<Container>& q) override;
    virtual void update_vivo(ListaObjetos& objetos, Queue<Container>& q) override;
    void throw_banana(ListaObjetos& objetos);
};


#endif
