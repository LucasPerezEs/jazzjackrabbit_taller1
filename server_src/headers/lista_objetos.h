#ifndef OBJETOS_H_
#define OBJETOS_H_

#include <vector>
#include <memory>

#include "../../common_src/headers/queue.h"
#include "../../common_src/headers/Container.h"

#include "objeto.h"

class ListaObjetos {
private:
public:
    std::vector<std::shared_ptr<Objeto>> objetos;
    ListaObjetos();
    void agregar_objeto(std::shared_ptr<Objeto> o);
    void eliminar_borrados(Queue<Container>& q);
    void update(Mapa& mapa, Queue<Container>& q);
    void correr_colisiones();
    void borrar();
    void borrar(int id);
};

#endif
