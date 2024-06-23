#include "../headers/enemigo.h"

#include <iostream>


Enemigo::Enemigo(float x, float y, float w, float h, float max_life, float speed, float damage,
                 float prob_carrot, float prob_ammo, float prob_goldcoin, EntityType en_type,
                 AnimationType an_type, std::map<std::string, float>& config):
        Ente(x, y, w, h, max_life, en_type, an_type),
        max_life(max_life),
        damage(damage),
        speed(speed),
        prob_carrot(prob_carrot),
        prob_ammo(prob_ammo),
        prob_goldcoin(prob_goldcoin),
        config(config) {
    direccion = 1;
    contador = 0;
}

void Enemigo::colision(Objeto& o) {
    if (check_colision(o)) {
        o.colision(*this);
    }
}
void Enemigo::colision(Personaje& p) {
    p.colision(*this);
    /*if (p.has_special_action_active()) {
        this->RecibirDanio(p.danio_ataque_especial);
    } else {
        std::cout << "Enemigo ataca" << std::endl;
        p.RecibirDanio(damage);
    }*/
}

void Enemigo::colision(Bala& b) {
    b.borrar = true;
    RecibirDanio(b.danio);
}

void Enemigo::drop_item(ListaObjetos& objetos, Queue<Container>& q) {
    srand(time(nullptr));
    int random_int = rand() % 100 + 1;

    Pickup* drop;


    if (random_int < prob_goldcoin) {
        drop = new Gold_Coin(x + width / 2, y + height / 3, config, q);

    } else if (random_int < prob_goldcoin + prob_carrot) {
        drop = new Zanahoria(x + width / 2, y + height / 3, config, q);

    } else if (random_int < 80) {
        drop = new ZanahoriaEnvenenada(x + width / 2, y + height / 3, config, q);

    } else if (random_int < prob_goldcoin + prob_carrot + prob_ammo) {
        drop = new Municion(x + width / 2, y + height / 3, config, q);

    } else {
        return;
    }

    objetos.agregar_objeto(static_cast<Pickup*>(drop));
    Container c(0, drop->id, drop->x, drop->y, drop->width, drop->height, 0, drop->an_type,
                drop->en_type, 0, 0, 0, "");
    q.try_push(c);
}

int Enemigo::get_damage() { return this->damage; }
