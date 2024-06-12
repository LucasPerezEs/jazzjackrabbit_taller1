#include "headers/enemigo.h"

#include <iostream>


Enemigo::Enemigo(float x, float y, float w, float h, EntityType en_type, AnimationType an_type,
                 std::map<std::string, float>& config):
        Ente(x, y, w, h, config["enemy_life"], en_type, an_type), config(config) {
    direccion = 1;
    danio = config["enemy_damage"];
    limxder = x + 20;  // cuanto se va a mover de izquierda a derecha
    limxizq = x - 20;
    limy = y + 0;  // por si lo queremos hacer volador
    // vida = 100;
    contador = 0;
}

void Enemigo::colision(Objeto& o) {
    if (check_colision(o)) {
        o.colision(*this);
    }
}
void Enemigo::colision(Personaje& p) {
    if (p.has_special_action_active()) {
        this->RecibirDanio(p.danio_ataque_especial);
    } else {
        p.RecibirDanio(danio);
    }
}

void Enemigo::colision(Bala& b) {
    b.borrar = true;
    RecibirDanio(b.danio);
}

void Enemigo::update(Mapa& m, ListaObjetos& objetos, Queue<Contenedor>& q) {
    float auxx = x;
    float auxy = y;  // se guarda la posicion actual
    // float auxw = width;
    // float auxh = height;
    bool colisionx;

    x += config["enemy_speed"] * direccion;
    // width += 0.25 * direccion;

    colisionx = m.CheckColision(x, auxy, width, height);

    if (colisionx || x > limxder || x < limxizq) {
        direccion = direccion * -1;  // si colisiona con la pos x actualizada
        x = auxx;                    // se pone la pos x anterior
        // width = auxw;
    }
    Contenedor c(0, this->id, this->x, this->y, this->width, this->height, this->direccion,
                 this->an_type, this->en_type, 0, 0, 0);
    q.try_push(c);
}

Pickup* Enemigo::drop_item() {
    srand(time(nullptr));
    int random_int = rand() % 100 + 1;

    float prob_goldcoin = config["enemy_prob_goldcoin"] * 100;
    float prob_carrot = config["enemy_prob_carrot"] * 100;
    float prob_ammo = config["enemy_prob_ammo"] * 100;

    if (random_int < prob_goldcoin) {
        Gold_Coin* drop = new Gold_Coin(x + width / 2, y + height / 3, config);
        return static_cast<Pickup*>(drop);

    } else if (random_int < prob_goldcoin + prob_carrot) {
        Zanahoria* drop = new Zanahoria(x + width / 2, y + height / 3, config);
        return static_cast<Pickup*>(drop);

    } else if (random_int < prob_goldcoin + prob_carrot + prob_ammo) {
        Municion* drop = new Municion(x + width / 2, y + height / 3, config);
        return static_cast<Pickup*>(drop);

    } else {
        return nullptr;
    }
}

void Enemigo::update_vivo(ListaObjetos& objetos, Queue<Contenedor>& q) {
    if (vida <= 0) {
        if (contador == 1) {  // si acaba de morir dropea una municion o moneda o zanahoria
            Pickup* drop = drop_item();
            if (!drop) {
                contador++;
                return;
            }
            objetos.agregar_objeto(drop);
            Contenedor c(0, drop->id, drop->x, drop->y, drop->width, drop->height, 0, drop->an_type,
                         drop->en_type, 0, 0, 0);
            q.try_push(c);
        }
        if (contador == 240) {  // despues de un rato revive
            vida = config["enemy_life"];
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
