#ifndef BANANA_H_
#define BANANA_H_

#include <map>
#include <string>

#include "../../common_src/headers/entity_commands.h"
#include "../../common_src/headers/queue.h"


#include "mapa.h"
#include "objeto.h"
#include "personaje.h"
#include "pickup.h"

class Banana: public Objeto {
protected:
    float vel;

public:
    int danio;
    Banana(float x, float y, int d, std::map<std::string, float>& config);
    virtual void colision(Objeto& o) override;
    virtual void colision(Personaje& o) override;
    virtual void colision(Enemigo& o) override;
    virtual void colision(Pickup& o) override;
    virtual void update(Mapa& m, ListaObjetos& objetos, Queue<Container>& q) override;
    virtual void eliminar() override;
};

#endif
