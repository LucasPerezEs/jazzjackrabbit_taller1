#include "headers/objeto.h"

#include <iostream>
#include <vector>

#include "headers/enemigo.h"
#include "headers/lista_objetos.h"
#include "headers/mapa.h"

int cant = 1;
int num = 0;

Objeto::Objeto(float x, float y, float w, float h): x(x), y(y), width(w), height(h), borrar(false) {
    id = num;
    num++;
}

Ente::Ente(float x, float y, float w, float h, int vida):
        Objeto(x, y, w, h),
        direccion(1),
        contador(0),
        vida(vida) {  // para la direccion 1 es a la derecha y -1 a la izquierda
    // int direccion = 1;
}


void Objeto::update(Mapa& m, ListaObjetos& objetos, Queue<Contenedor>& q) {}
void Objeto::eliminar() {}
void Objeto::colision(Personaje& o) {}  //       Por defecto los objetos no hacen nada
void Objeto::colision(Enemigo& o) {
}  //       Le decis vos que queres que hagan o con que pueden interacturar
void Objeto::colision(Bala& o) {}
void Objeto::colision(Municion& m) {}
Objeto::~Objeto() {}

void Ente::RecibirDanio(int d) {
    vida -= d;
    if (vida <= 0) {  // si muere se borra del vector de colisiones
        borrar = true;
    }
}

bool Ente::vivo() { return vida > 0; }

void Ente::update_vivo(ListaObjetos& objetos, Queue<Contenedor>& q) {
    if (vida <= 0) {
        if (contador ==
            240) {  // revive despues de tantos ciclos y lo agrego al vector de colisiones
            vida = 100;
            borrar = false;
            objetos.agregar_objeto(this);
            contador = 0;
            Contenedor c(this->id, this->x, this->y, this->width, this->height, this->borrar);
            q.try_push(c);
        }
        contador++;
    }
}
