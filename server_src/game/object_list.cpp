#include "../headers/object_list.h"

#include <algorithm>
#include <iostream>
#include <vector>

ObjectList::ObjectList() {}

void ObjectList::agregar_objeto(std::shared_ptr<Object> o) { objetos.push_back(o); }

void ObjectList::update(Map& mapa, Queue<Container>& q) {
    int size = objetos.size();
    for (int i = 0; i < size; i++) {
        objetos[i]->update(mapa, *this, q);
    }
}

void ObjectList::correr_colisiones() {
    for (long unsigned int i = 0; i < objetos.size(); i++) {
        for (long unsigned int j = i; j < objetos.size(); j++) {
            objetos[i]->colision(*objetos[j]);
        }
    }
}

void ObjectList::eliminar_borrados(Queue<Container>& q) {
    objetos.erase(std::remove_if(objetos.begin(), objetos.end(),
                                 [&](std::shared_ptr<Object> o) {
                                     if (o->borrar) {
                                         Container c(1, o->id, 0, 0, 0, 0, 0,
                                                     AnimationType::NONE_ANIMATION,
                                                     EntityType::NONE_ENTITY, 0,
                                                     {EntityType::NONE_ENTITY, 0}, 0, "");
                                         q.try_push(c);
                                         return true;
                                     }
                                     return false;
                                 }),
                  objetos.end());
}


void ObjectList::borrar() { objetos.clear(); }

void ObjectList::borrar(int id) {
    objetos.erase(std::remove_if(objetos.begin(), objetos.end(), [&](std::shared_ptr<Object> o) {
        if (o->id == id) {
            return true;
        }
        return false;
    }));
}
