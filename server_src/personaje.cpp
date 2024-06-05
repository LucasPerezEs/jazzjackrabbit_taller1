#include "headers/personaje.h"

#include <iostream>
#include <map>

#include "headers/enemigo.h"
#include "headers/lista_objetos.h"
#include "headers/municion.h"

Personaje::Personaje(float x, float y, float w, float h, int vida, EntityType en_type,
                     AnimationType an_type):
        Ente(x, y, w + x, h + y, vida, en_type, an_type), tiempo(std::chrono::system_clock::now()) {
    velx = 0.5;
    vely = 0;
    direccion = 1;
    jumping = false;
    movingright = false;
    movingleft = false;
    disparando = false;
    contador = 0;
    municion = 20;
    espera_idle = 2000;  // en milisegundos
    espera_shoot = 250;  // Misma que la del arma
    score = 0;
}

void Personaje::moveRigth() {
    movingright = true;
    direccion = 1;
    an_type = AnimationType::WALK;
    tiempo = std::chrono::system_clock::now();
}
void Personaje::moveLeft() {
    movingleft = true;
    direccion = -1;
    an_type = AnimationType::INTOXICATED_WALK;  // Prueba
    tiempo = std::chrono::system_clock::now();
}
void Personaje::stopMovingRight() {
    movingright = false;
    an_type = AnimationType::SHOOT_IDLE;
}

void Personaje::stopMovingLeft() {
    movingleft = false;
    an_type = AnimationType::SHOOT_IDLE;
}

void Personaje::run() {
    velx = 1.2;
    // an_type = AnimationType::RUN;
}

void Personaje::stoprunning() {
    velx = 0.5;
    // an_type = AnimationType::IDLE;
}

void Personaje::jump() {
    if (!jumping) {  // Esto es para evitar que se pueda spamear el jump y volar
        vely = 3;
        jumping = true;
        // Mas adelante estaria bueno detectar cuando esta cayendo y poner animacion FALL, en vez de
        // todo junto pq no llega a terminar la animacion.
        an_type = AnimationType::JUMP;
        tiempo = std::chrono::system_clock::now();
    }
}

void Personaje::add_score(int score) {
    this->score += score;
    std::cout << "Puntos: " << this->score << std::endl;
}

void Personaje::update(Mapa& m, ListaObjetos& objetos, Queue<Contenedor>& q) {
    if (disparando) {
        disparar(objetos);  // Creo que ahora con sender y receiver esto se puede poner afuera
    }

    if (!(movingleft || movingright || disparando || jumping) &&
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

    float auxx = x;
    float auxy = y;  // se guarda la posicion actual
    float auxw = width;
    float auxh = height;
    bool colisionx;
    bool colisiony;
    if (!(movingleft && movingright) &&
        (movingleft || movingright)) {  // mientras se este apretando una tecla de mover el jugador
        if (movingleft) {
            x += velx * -1;  // se actualiza la posicin en x
            width += velx * -1;
        }
        if (movingright) {
            x += velx;  // se actualiza la posicin en x
            width += velx;
        }
    }
    y += vely;
    height += vely;
    vely -= 0.4;  // esto es la aceleracion de la gravedad, se tiene que poner un limite de vely

    colisionx = m.CheckColision(x, auxy, width, auxh);
    colisiony = m.CheckColision(auxx, y, auxw, height);

    if (colisionx) {   // si colisiona con la pos x actualizada
        x = auxx;      // se pone la pos x anterior
        width = auxw;  // lo mismo con la pos y
    }
    if (colisiony) {
        jumping = false;  // esta en el piso se puede saltar
        vely = 0;
        y = auxy;
        height = auxh;
    }
    if (!(colisionx && colisiony)) {  // me fijo si justo se da el caso que solo choca en diagonal
        if (m.CheckColision(x, y, width, height)) {
            x = auxx;  // se pone la pos x anterior
            width = auxw;
        }
    }
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
    if (this == &o) {
        return;
    }
    if (x < (o.width) && (width) > o.x && y < (o.height) && (height) > o.y) {
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
            1) {      // Si se dispara mirando a la derecha la bala sale desde la derecha del objeto
            aux = w;  // Si se dispara mirando a la izquierda sale a la izquierda
        } else {
            aux = x;
        }

        Bala* b = new Bala(aux, (y + h) / 2, d);
        objetos.agregar_objeto(b);  // Se agrega al vector de colisiones
        // disminuir_municion();
    }
}

void Arma::disminuir_municion() { municion--; }


Bala::Bala(float x, float y, int d):
        Objeto(x, y, x + 1, y + 1, EntityType::BULLET,
               AnimationType::WALK) {  // se le pasa la direccion a la que va a salir la bala por
                                       // parametro
    vel = 2 * d;
    danio = 10;
}

void Bala::colision(Objeto& o) {
    if (this == &o) {
        return;
    }
    if (x < (o.width) && (width) > o.x && y < (o.height) && (height) > o.y) {
        o.colision(*this);
    }
}

void Bala::colision(Enemigo& o) { o.colision(*this); }

void Bala::update(
        Mapa& mapa, ListaObjetos& objetos,
        Queue<Contenedor>& q) {  // actualiza la posicion, si choca con el mapa se tiene que borrar
    x += vel;
    width += vel;
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
