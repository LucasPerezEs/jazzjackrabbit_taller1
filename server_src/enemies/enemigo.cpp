#include "../headers/enemigo.h"

#include <iostream>

#include "../headers/projectile.h"


Enemigo::Enemigo(float x, float y, float w, float h, float max_life, float speed, float damage,
                 float prob_carrot, float prob_ammo, float prob_goldcoin, float prob_rocket,
                 float prob_gem, EntityType en_type, AnimationType an_type,
                 std::map<std::string, float>& config):
        Ente(x, y, w, h, max_life, en_type, an_type),
        max_life(max_life),
        damage(damage),
        speed(speed),
        prob_carrot(prob_carrot),
        prob_ammo(prob_ammo),
        prob_goldcoin(prob_goldcoin),
        prob_rocket(prob_rocket),
        prob_gem(prob_gem),
        config(config) {
    direccion = 1;
    contador = 0;
    spawn = 1;
}

void Enemigo::colision(Objeto& o) {
    if (check_colision(o)) {
        o.colision(*this);
    }
}
void Enemigo::colision(Personaje& p) { p.colision(*this); }

void Enemigo::colision(Projectile& b) {
    if (b.en_type != EntityType::ROCKET) {
        b.borrar = true;
    }
    RecibirDanio(b.danio);
}

void Enemigo::drop_item(ListaObjetos& objetos, Queue<Container>& q) {
    srand(time(nullptr));
    int random_int = rand() % 100 + 1;

    if (random_int < prob_goldcoin) {
        std::shared_ptr<Gold_Coin> drop(new Gold_Coin(x + width / 2, y + height / 3, config, q));
        objetos.agregar_objeto(drop);
        Container c(0, drop->id, drop->x, drop->y, drop->width, drop->height, 0, drop->an_type,
                    drop->en_type, 0, {EntityType::NONE_ENTITY, 0}, 0, "");
        q.try_push(c);

    } else if (random_int < prob_goldcoin + prob_carrot) {
        int random_carrot = rand() % 100 + 1;

        if (random_carrot < 15) {
            std::shared_ptr<Zanahoria> drop(
                    new Zanahoria(x + width / 2, y + height / 3, config, q));
            objetos.agregar_objeto(drop);
            Container c(0, drop->id, drop->x, drop->y, drop->width, drop->height, 0, drop->an_type,
                        drop->en_type, 0, {EntityType::NONE_ENTITY, 0}, 0, "");
            q.try_push(c);
        } else {
            std::shared_ptr<ZanahoriaEnvenenada> drop(
                    new ZanahoriaEnvenenada(x + width / 2, y + height / 3, config, q));
            objetos.agregar_objeto(drop);
            Container c(0, drop->id, drop->x, drop->y, drop->width, drop->height, 0, drop->an_type,
                        drop->en_type, 0, {EntityType::NONE_ENTITY, 0}, 0, "");
            q.try_push(c);
        }

    } else if (random_int < prob_goldcoin + prob_carrot + prob_ammo) {
        std::shared_ptr<Municion> drop(new Municion(x + width / 2, y + height / 3, config, q));
        objetos.agregar_objeto(drop);
        Container c(0, drop->id, drop->x, drop->y, drop->width, drop->height, 0, drop->an_type,
                    drop->en_type, 0, {EntityType::NONE_ENTITY, 0}, 0, "");
        q.try_push(c);

    } else if (random_int < prob_goldcoin + prob_carrot + prob_ammo + prob_rocket) {
        std::shared_ptr<RocketPickup> drop(
                new RocketPickup(x + width / 2, y + height / 3, config, q));
        objetos.agregar_objeto(drop);
        Container c(0, drop->id, drop->x, drop->y, drop->width, drop->height, 0, drop->an_type,
                    drop->en_type, 0, {EntityType::NONE_ENTITY, 0}, 0, "");
        q.try_push(c);

    } else if (random_int < prob_goldcoin + prob_carrot + prob_ammo + prob_rocket + prob_gem) {
        std::shared_ptr<Gem> drop(new Gem(x + width / 2, y + height / 3, config, q));
        objetos.agregar_objeto(drop);
        Container c(0, drop->id, drop->x, drop->y, drop->width, drop->height, 0, drop->an_type,
                    drop->en_type, 0, {EntityType::NONE_ENTITY, 0}, 0, "");
        q.try_push(c);

    } else {
        return;
    }
}

int Enemigo::get_damage() { return this->damage; }
