#include "../headers/lista_objetos.h"

#include <algorithm>
#include <iostream>
#include <vector>

ListaObjetos::ListaObjetos() {}

void ListaObjetos::agregar_objeto(std::shared_ptr<Objeto> o) { objetos.push_back(o); }

void ListaObjetos::update(Mapa& mapa, Queue<Container>& q) {
    int size = objetos.size();
    for (int i = 0; i < size; i++) {
        objetos[i]->update(mapa, *this, q);
    }
}

void ListaObjetos::correr_colisiones() {
    for (long unsigned int i = 0; i < objetos.size(); i++) {
        for (long unsigned int j = i; j < objetos.size(); j++) {
            objetos[i]->colision(*objetos[j]);
        }
    }
}

void ListaObjetos::eliminar_borrados(Queue<Container>& q) {
    objetos.erase(std::remove_if(objetos.begin(), objetos.end(),
                                 [&](std::shared_ptr<Objeto> o) {
                                     if (o->borrar) {
                                         Container c(1, o->id, 0, 0, 0, 0, 0,
                                                     AnimationType::NONE_ANIMATION,
                                                     EntityType::NONE_ENTITY, 0,
                                                     {EntityType::NONE_ENTITY, 0}, 0, "");
                                         // Al borrar solo hace falta el id
                                         q.try_push(c);
                                         // o->eliminar();
                                         return true;
                                     }
                                     return false;
                                 }),
                  objetos.end());
}


void ListaObjetos::borrar() {
    /*for (auto objeto: objetos) {
        delete objeto;
    }*/
    objetos.clear();
}

void ListaObjetos::borrar(int id) {
    objetos.erase(std::remove_if(objetos.begin(), objetos.end(), [&](std::shared_ptr<Objeto> o) {
        if (o->id == id) {
            // delete o;
            return true;
        }
        return false;
    }));
}
