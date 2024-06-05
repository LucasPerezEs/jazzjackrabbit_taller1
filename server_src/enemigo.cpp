#include "headers/enemigo.h"

#include <iostream>

#include "headers/gold_coin.h"
#include "headers/lista_objetos.h"
#include "headers/municion.h"
#include "headers/personaje.h"
#include "headers/zanahoria.h"


Enemigo::Enemigo(float x, float y, float w, float h, int vida, EntityType en_type,
                 AnimationType an_type):
        Ente(x, y, w + x, h + y, vida, en_type, an_type) {
    direccion = 1;
    danio = 1;
    limxder = x + 20;  // cuanto se va a mover de izquierda a derecha
    limxizq = x - 20;
    limy = y + 0;  // por si lo queremos hacer volador
    // vida = 100;
    contador = 0;
}

void Enemigo::colision(Objeto& o) {
    if (this == &o) {
        return;
    }
    if (x < (o.width) && (width) > o.x && y < (o.height) && (height) > o.y) {
        o.colision(*this);
    }
}
void Enemigo::colision(Personaje& p) { p.RecibirDanio(danio); }
void Enemigo::colision(Bala& b) {
    b.borrar = true;
    RecibirDanio(b.danio);
}

void Enemigo::update(Mapa& m, ListaObjetos& objetos, Queue<Contenedor>& q) {
    float auxx = x;
    float auxy = y;  // se guarda la posicion actual
    float auxw = width;
    float auxh = height;
    bool colisionx;

    x += 0.25 * direccion;
    width += 0.25 * direccion;

    colisionx = m.CheckColision(x, auxy, width, auxh);

    if (colisionx || x > limxder || x < limxizq) {
        direccion = direccion * -1;  // si colisiona con la pos x actualizada
        x = auxx;                    // se pone la pos x anterior
        width = auxw;
    }
    Contenedor c(0, this->id, this->x, this->y, this->width, this->height, this->direccion,
                 this->an_type, this->en_type, 0, 0, 0);
    q.try_push(c);
}

void Enemigo::update_vivo(ListaObjetos& objetos, Queue<Contenedor>& q) {
    if (vida <= 0) {
        if (contador == 1) {  // si acaba de morir dropea una municion o moneda o zanahoria
            Gold_Coin* drop = new Gold_Coin((x + width) / 2, (y + height) / 3);
            objetos.agregar_objeto(drop);
            Contenedor c(0, drop->id, drop->x, drop->y, drop->width, drop->height, 0, drop->an_type,
                         drop->en_type, 0, 0, 0);
            q.try_push(c);
        }
        if (contador == 240) {  // despues de un rato revive
            vida = 100;
            borrar = false;
            objetos.agregar_objeto(this);
            contador = 0;
            Contenedor c(0, this->id, this->x, this->y, this->width, this->height, this->direccion,
                         AnimationType::WALK, EntityType::ENEMY, 0, 0, 0);
            q.try_push(c);
        }
        contador++;
    }
}
