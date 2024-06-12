#include "headers/personaje.h"

#include <iostream>
#include <map>

#include "headers/enemigo.h"
#include "headers/lista_objetos.h"
#include "headers/municion.h"

Personaje::Personaje(float x, float y, float w, float h, EntityType en_type, AnimationType an_type,
                     std::map<std::string, float>& config):
        Ente(x, y, w, h, config["player_life"], en_type, an_type),
        tiempo(std::chrono::system_clock::now()),
        config(config),
        arma(config) {
    velx = config["player_speed"];
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
    danio_ataque_especial = config["player_special_attack_dmg"];
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
    velx = config["player_run_speed"];
    // an_type = AnimationType::RUN;
}

void Personaje::stoprunning() {
    velx = config["player_speed"];
    // an_type = AnimationType::IDLE;
}

void Personaje::jump() {
    if (!jumping) {  // Esto es para evitar que se pueda spamear el jump y volar
        vely = config["player_jump"];
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
        vely = config["player_jump"] + 1;
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

    // float auxw = width;
    // float auxh = height;
    if (!(movingleft && movingright) &&
        (movingleft || movingright)) {  // mientras se este apretando una tecla de mover el jugador
        if (movingleft) {
            x += velx * -1;  // se actualiza la posicin en x
            // width += velx * -1;
        }
        if (movingright) {
            x += velx;  // se actualiza la posicin en x
            // width += velx;
        }
    }
    y += vely;
    // height += vely;
    vely -= config["gravity"];  // esto es la aceleracion de la gravedad, se tiene que poner un
                                // limite de vely
}

void Personaje::check_colisions(Mapa& m, int aux_x, int aux_y) {

    bool colisionx;
    bool colisiony;
    colisionx = m.CheckColision(x, aux_y, width, height);
    colisiony = m.CheckColision(aux_x, y, width, height);

    if (colisionx) {  // si colisiona con la pos x actualizada
        x = aux_x;    // se pone la pos x anterior
        // width = auxw;  // lo mismo con la pos y
    }
    if (colisiony) {
        jumping = false;  // esta en el piso se puede saltar
        vely = 0;
        y = aux_y;
        // height = auxh;
        if (this->en_type == EntityType::JAZZ) {
            special_action_active = false;
        }
    }
    if (!(colisionx && colisiony)) {  // me fijo si justo se da el caso que solo choca en diagonal
        if (m.CheckColision(x, y, width, height)) {
            x = aux_x;  // se pone la pos x anterior
            // width = auxw;
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
            vida = config["player_life"];
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


Arma::Arma(std::map<std::string, float>& config):
        tiempo(std::chrono::system_clock::now()), config(config) {
    espera = 1000 / config["weapon_firerate"];  // en milisegundos
    municion = config["weapon_initial_ammo"];
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

        Bala* b = new Bala(aux, y + h / 2, d, config);
        objetos.agregar_objeto(b);  // Se agrega al vector de colisiones
        // disminuir_municion();
    }
}

void Arma::disminuir_municion() { municion--; }

// cppcheck-suppress constParameter
Bala::Bala(float x, float y, int d, std::map<std::string, float>& config):
        Objeto(x, y, 1, 1, EntityType::BULLET,
               AnimationType::WALK) {  // se le pasa la direccion a la que va a salir la bala por
                                       // parametro
    vel = config["bullet_speed"] * d;
    danio = config["bullet_damage"];
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
