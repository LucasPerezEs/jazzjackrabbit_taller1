#ifndef OBJETOS_H_
#define OBJETOS_H_

#include <vector>

#include "../../common_src/headers/queue.h"

#include "contenedor.h"
#include "objeto.h"

class ListaObjetos {
private:
public:
    std::vector<Objeto*> objetos;
    ListaObjetos();
    void agregar_objeto(Objeto* o);
    void eliminar_borrados(Queue<Contenedor>& q);
    void update(Mapa& mapa, Queue<Contenedor>& q);
    void correr_colisiones();
};

#endif
