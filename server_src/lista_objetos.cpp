#include "headers/lista_objetos.h"

#include <algorithm>
#include <iostream>
#include <vector>

ListaObjetos::ListaObjetos() {}

void ListaObjetos::agregar_objeto(Objeto* o) { objetos.push_back(o); }

void ListaObjetos::update(Mapa& mapa, Queue<Contenedor>& q) {
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

void ListaObjetos::eliminar_borrados(Queue<Contenedor>& q) {
    objetos.erase(std::remove_if(objetos.begin(), objetos.end(),
                                 [&](Objeto* o) {
                                     if (o->borrar) {
                                         Contenedor c(1, o->id, 0, 0, 0, 0, 0,
                                                      AnimationType::NONE_ANIMATION,
                                                      EntityType::NONE_ENTITY);
                                         // Al borrar solo hace falta el id
                                         q.try_push(c);
                                         return true;
                                     }
                                     return false;
                                 }),
                  objetos.end());
}
