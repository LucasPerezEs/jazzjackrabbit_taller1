#include "headers/personaje.h"

#include <iostream>
#include <map>
#include <cmath>

#include "headers/enemigo.h"
#include "headers/lista_objetos.h"
#include "headers/municion.h"

Personaje::Personaje(float x, float y, float w, float h, int vida, EntityType en_type,
                     AnimationType an_type):
        Ente(x, y, w, h, vida, en_type, an_type), tiempo(std::chrono::system_clock::now()) {
    velx = 0.5;
    vely = 0;
    direccion = 1;
    jumping = false;
    movingright = false;
    movingleft = false;
    disparando = false;
    special_action_active = false;
    contador = 0;
    municion = 20;
    espera_idle = 2000;  // en milisegundos
    espera_shoot = 250;  // Misma que la del arma
    score = 0;
    danio_ataque_especial = 100;
    direccion_movimientox = 1;
}

void Personaje::moveRigth() {
    if (special_action_active) {
        return;
    }

    movingright = true;
    direccion = 1;
    an_type = AnimationType::WALK;
    tiempo = std::chrono::system_clock::now();
}
void Personaje::moveLeft() {
    if (special_action_active) {
        return;
    }
    movingleft = true;
    direccion = -1;
    an_type = AnimationType::INTOXICATED_WALK;  // Prueba
    tiempo = std::chrono::system_clock::now();
}
void Personaje::stopMovingRight() {
    movingright = false;
    if (!jumping && !special_action_active) {
        an_type = AnimationType::SHOOT_IDLE;
    }
}

void Personaje::stopMovingLeft() {
    movingleft = false;
    if (!jumping && !special_action_active) {
        an_type = AnimationType::SHOOT_IDLE;
    }
}

void Personaje::run() {
    velx = 1;
    // an_type = AnimationType::RUN;
}

void Personaje::stoprunning() {
    velx = 0.5;
    // an_type = AnimationType::IDLE;
}

void Personaje::jump() {
    if (!jumping) {  // Esto es para evitar que se pueda spamear el jump y volar
        vely = 1;
        jumping = true;
        an_type = AnimationType::JUMP;
        tiempo = std::chrono::system_clock::now();
    }
}

void Personaje::special_action() {
    if (!special_action_active) {
        special_action_active = true;
        movingleft = false;
        movingright = false;
        vely = 1.5;
        jumping = true;
        an_type = AnimationType::SPECIAL_ACTION;
        tiempo = std::chrono::system_clock::now();
    }
}

bool Personaje::has_special_action_active() { return special_action_active; }

void Personaje::add_score(int score) {
    this->score += score;
    std::cout << "Puntos: " << this->score << std::endl;
}

void Personaje::check_idle() {

    if (!movingleft && !movingright && !disparando && !jumping &&
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() -
                                                              tiempo)
                        .count() > espera_idle) {
        an_type = AnimationType::IDLE;

    } else if (!movingleft && !movingright && !jumping &&
               std::chrono::duration_cast<std::chrono::milliseconds>(
                       std::chrono::system_clock::now() - tiempo)
                               .count() > espera_shoot) {
        an_type = AnimationType::SHOOT_IDLE;
    }
}

void Personaje::update_position() {

    if (!(movingleft && movingright) &&
        (movingleft || movingright)) {  // mientras se este apretando una tecla de mover el jugador
        if (movingleft) {
            x += velx * -1 * direccion_movimientox;
            y += velx * -1 * direccion_movimientoy; // se actualiza la posicin en x
        }
        if (movingright) {
            x += velx * direccion_movimientox;  // se actualiza la posicin en x
            y += velx * direccion_movimientoy;
        }
    }
    y += vely;
    vely -= 0.1;  // esto es la aceleracion de la gravedad, se tiene que poner un limite de vely
}

void Personaje::check_colisions(Mapa& m, float aux_x, float aux_y) {

    bool colisionx = false;
    bool colisiony = false;
    bool colisiondiagonal = false;

    for (auto diagonal: m.diagonalesDer) {

        if (diagonal->x <= x + width && x + width <= diagonal->x + diagonal->w && y <= diagonal->y + diagonal->h - (diagonal->x + diagonal->w - (x + width)) && diagonal->y + diagonal->h - (diagonal->x + diagonal->w - (x + width)) <= y + height/2) {
            jumping = false;
            vely = 0;
            y = diagonal->y + diagonal->h - (diagonal->x + diagonal->w - (x + width));
            special_action_active = false;
            colisiony = true;
            colisionx = true;
            direccion_movimientox = sqrt(2)/2;
            direccion_movimientoy = sqrt(2)/2;
            colisiondiagonal = true;
        }
        else {
            if (aux_x < (diagonal->x + diagonal->w) && (aux_x + width) > diagonal->x && (y + 2*height/3) < diagonal->y && diagonal->y < y + height) {
                vely = 0;
                y = diagonal->y - height;
                special_action_active = false;
                colisiony = true;
            }
            if (x < (diagonal->x + diagonal->w) && (diagonal->x + diagonal->w) < x + width/2 && aux_y < (diagonal->y + diagonal->h) && (aux_y + height) > diagonal->y) {
                x = diagonal->x + diagonal->w;
                colisionx = true;
            }
        }

    }

    for (auto diagonal: m.diagonalesIzq) {

        if (diagonal->x <= x && x <= diagonal->x + diagonal->w && y <= diagonal->y + diagonal->h - (x - diagonal->x) && diagonal->y + diagonal->h - (x - diagonal->x) <= y + height/2) {
            jumping = false;
            vely = 0;
            y = diagonal->y + diagonal->h - (x - diagonal->x);
            special_action_active = false;
            colisiony = true;
            colisionx = true;
            direccion_movimientox = sqrt(2)/2;
            direccion_movimientoy = -sqrt(2)/2;
            colisiondiagonal = true;
        }
        else {
            if (aux_x < (diagonal->x + diagonal->w) && (aux_x + width) > diagonal->x && (y + 2*height/3) < diagonal->y && diagonal->y < y + height) {
                vely = 0;
                y = diagonal->y - height;
                special_action_active = false;
                colisiony = true;
            }
            if (x + width/2 < diagonal->x && diagonal->x < x + width && aux_y < (diagonal->y + diagonal->h) && (aux_y + height) > diagonal->y) {
                x = diagonal->x - width;
                colisionx = true;
            }
        }
    }

    if (!colisiondiagonal) {
        direccion_movimientox = 1;
        direccion_movimientoy = 0;
    }

    for (auto terreno: m.objetos) {
        if (aux_x < (terreno->x + terreno->w) && (aux_x + width) > terreno->x && (y + 2*height/3) < (terreno->y + terreno->h) && (y + height) > terreno->y) {
            vely = 0;
            y = terreno->y - height;
            special_action_active = false;
            colisiony = true;
        }
        else if (aux_x < (terreno->x + terreno->w) && (aux_x + width) > terreno->x && y < (terreno->y + terreno->h) && (y + height/4) > terreno->y) {
            jumping = false;
            vely = 0;
            y = terreno->y + terreno->h;
            special_action_active = false;
            colisiony = true;
        }

        if (x < (terreno->x + terreno->w) && (x + width/2) > terreno->x && aux_y < (terreno->y + terreno->h) && (aux_y + height) > terreno->y) {
            x = terreno->x + terreno->w;
            colisionx = true;
        }
        else if ((x + width/2) < (terreno->x + terreno->w) && (x + width) > terreno->x && aux_y < (terreno->y + terreno->h) && (aux_y + height) > terreno->y) {
            x = terreno->x - width;
            colisionx = true;
        }
    }

    if (!(colisionx && colisiony)) {  // me fijo si justo se da el caso que solo choca en diagonal
        if (m.CheckColision(x, y, width, height)) {
            x = aux_x;  // se pone la pos x anterior
        }
    }


}

void Personaje::update(Mapa& m, ListaObjetos& objetos, Queue<Contenedor>& q) {
    if (disparando) {
        disparar(objetos);  // Creo que ahora con sender y receiver esto se puede poner afuera
    }

    float aux_x = x;
    float aux_y = y;  // se guarda la posicion actual

    check_idle();

    update_position();

    check_colisions(m, aux_x, aux_y);

    Contenedor c(3, this->id, this->x, this->y, this->width, this->height, this->direccion,
                 this->an_type, this->en_type, this->vida, this->municion, this->score);
    q.try_push(c);
}

void Personaje::update_vivo(ListaObjetos& objetos, Queue<Contenedor>& q) {
    if (vida <= 0) {
        if (contador ==
            240) {  // revive despues de tantos ciclos y lo agrego al vector de colisiones
            vida = 100;
            borrar = false;
            objetos.agregar_objeto(this);
            contador = 0;
            Contenedor c(3, this->id, this->x, this->y, this->width, this->height, this->direccion,
                         this->an_type, this->en_type, this->vida, this->municion, this->score);
            q.try_push(c);
        }
        contador++;
    }
}


void Personaje::colision(Objeto& o) {
    if (check_colision(o)) {
        o.colision(*this);
    }
}
void Personaje::colision(Enemigo& e) { e.colision(*this); }

void Personaje::colision(Municion& m) { m.colision(*this); }

void Personaje::disparar(ListaObjetos& objetos) {
    tiempo = std::chrono::system_clock::now();
    arma.disparar(objetos, x, width, y, height, direccion);
    if (!movingleft && !movingright) {
        an_type = AnimationType::SHOOT;
    }
}

void Personaje::set_id(int i) { id = i; }


Arma::Arma(): tiempo(std::chrono::system_clock::now()) {
    espera = 250;  // en milisegundos
    municion = 10;
}

void Arma::disparar(ListaObjetos& objetos, float x, float w, float y, float h, int d) {
    if (municion > 0 && std::chrono::duration_cast<std::chrono::milliseconds>(
                                std::chrono::system_clock::now() - tiempo)
                                        .count() > espera) {
        tiempo = std::chrono::system_clock::now();
        int aux;
        if (d ==
            1) {  // Si se dispara mirando a la derecha la bala sale desde la derecha del objeto
            aux = x + w;  // Si se dispara mirando a la izquierda sale a la izquierda
        } else {
            aux = x + w;
        }

        Bala* b = new Bala(aux, y + h / 2, d);
        objetos.agregar_objeto(b);  // Se agrega al vector de colisiones
        // disminuir_municion();
    }
}

void Arma::disminuir_municion() { municion--; }


Bala::Bala(float x, float y, int d):
        Objeto(x, y, 1, 1, EntityType::BULLET,
               AnimationType::WALK) {  // se le pasa la direccion a la que va a salir la bala por
                                       // parametro
    vel = 1.5 * d;
    danio = 10;
}

void Bala::colision(Objeto& o) {
    if (check_colision(o)) {
        o.colision(*this);
    }
}

void Bala::colision(Enemigo& o) { o.colision(*this); }

void Bala::update(
        Mapa& mapa, ListaObjetos& objetos,
        Queue<Contenedor>& q) {  // actualiza la posicion, si choca con el mapa se tiene que borrar
    x += vel;
    // width += vel;
    if (mapa.CheckColision(x, y, width, height)) {
        this->borrar = true;
    }
    Contenedor c(0, this->id, this->x, this->y, this->width, this->height, 0, this->an_type,
                 this->en_type, 0, 0, 0);
    q.try_push(c);
}

void Bala::eliminar() {  // Para los memory leaks
    delete (this);
}
