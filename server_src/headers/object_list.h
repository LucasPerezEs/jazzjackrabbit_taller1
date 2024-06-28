#ifndef OBJETOS_H_
#define OBJETOS_H_

#include <memory>
#include <vector>

#include "../../common_src/headers/Container.h"
#include "../../common_src/headers/queue.h"

#include "object.h"

class ObjectList {
private:
public:
    std::vector<std::shared_ptr<Object>> objetos;
    ObjectList();
    void agregar_objeto(std::shared_ptr<Object> o);
    void eliminar_borrados(Queue<Container>& q);
    void update(Map& mapa, Queue<Container>& q);
    void correr_colisiones();
    void borrar();
    void borrar(int id);
};

#endif
