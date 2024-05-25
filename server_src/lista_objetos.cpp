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
                                         Contenedor c(o->id, o->x, o->y, o->width, o->height,
                                                      o->borrar);
                                         q.try_push(c);
                                         return true;
                                     }
                                     return false;
                                 }),
                  objetos.end());
}
