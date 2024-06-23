#include "../headers/objeto.h"

#include <iostream>
#include <vector>

#include "../headers/enemigo.h"
#include "../headers/lista_objetos.h"
#include "../headers/mapa.h"
#include "../headers/projectile.h"

int cant = 1;
int num = 20;

Objeto::Objeto(float x, float y, float w, float h, EntityType en_type, AnimationType an_type):
        x(x), y(y), width(w), height(h), borrar(false), en_type(en_type), an_type(an_type) {
    id = num;
    num++;
}

Ente::Ente(float x, float y, float w, float h, int vida, EntityType en_type, AnimationType an_type):
        Objeto(x, y, w, h, en_type, an_type), direccion(1), contador(0), vida(vida) {}


void Objeto::update(Mapa& m, ListaObjetos& objetos, Queue<Container>& q) {}
void Objeto::eliminar() {}

bool Objeto::check_colision(Objeto& o) {
    if (this == &o) {
        return false;
    }
    if (x < (o.x + o.width) && (x + width) > o.x && y < (o.y + o.height) && (y + height) > o.y) {
        return true;
    }
    return false;
}

void Objeto::colision(Personaje& o) {}  //       Por defecto los objetos no hacen nada
void Objeto::colision(Enemigo& o) {
}  //       Le decis vos que queres que hagan o con que pueden interacturar
void Objeto::colision(Projectile& o) {}
void Objeto::colision(Pickup& o) {}
void Objeto::colision(Municion& m) {}
void Objeto::colision(Banana& b) {}
void Objeto::colision(ZanahoriaEnvenenada& ze) {}

Objeto::~Objeto() {}

void Ente::RecibirDanio(int d) {
    vida -= d;
    if (vida <= 0) {  // si muere se borra del vector de colisiones
        borrar = true;
    }
}

bool Ente::vivo() { return vida > 0; }

void Ente::update_vivo(ListaObjetos& objetos, Queue<Container>& q,
                       std::unordered_map<uint32_t, Personaje*>& clientCharacters) {
    if (vida <= 0) {
        if (contador ==
            240) {  // revive despues de tantos ciclos y lo agrego al vector de colisiones
            vida = 100;
            borrar = false;
            objetos.agregar_objeto(this);
            contador = 0;
            Container c(0, this->id, this->x, this->y, this->width, this->height, this->direccion,
                        this->an_type, this->en_type, 0, 0, 0);
            q.try_push(c);
        }
        contador++;
    }
}
