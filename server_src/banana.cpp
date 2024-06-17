#include "headers/banana.h"

// cppcheck-suppress constParameter
Banana::Banana(float x, float y, int d, std::map<std::string, float>& config):
        Objeto(x, y, 2, 2, EntityType::BANANA,
               AnimationType::WALK) {  // se le pasa la direccion a la que va a salir la Banana por
                                       // parametro
    vel = config["banana_speed"] * d;
    danio = config["banana_damage"];
}

void Banana::colision(Objeto& o) {
    if (check_colision(o)) {
        o.colision(*this);
    }
}

void Banana::colision(Enemigo& o) {}

void Banana::colision(Pickup& o) {}

void Banana::colision(Personaje& p) { p.colision(*this); }

void Banana::update(
        Mapa& mapa, ListaObjetos& objetos,
        Queue<Container>& q) {  // actualiza la posicion, si choca con el mapa se tiene que borrar
    x += vel;
    // width += vel;
    if (mapa.CheckColision(x, y, width, height)) {
        this->borrar = true;
    }
    Container c(0, this->id, this->x, this->y, this->width, this->height, 0, this->an_type,
                this->en_type, 0, 0, 0);
    q.try_push(c);
}

void Banana::eliminar() {  // Para los memory leaks
    delete (this);
}
