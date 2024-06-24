#include "../headers/rocket.h"

Rocket::Rocket(float x, float y, int d, int shooter_id, std::map<std::string, float>& config):
        Projectile(x, y, d, shooter_id, EntityType::ROCKET, AnimationType::WALK,
                   config["rocket_speed"], config["rocket_damage"]),
        wait_explosion(250),
        exploded(false) {}

void Rocket::colision(Objeto& o) {
    if (check_colision(o) && !exploded) {
        tiempo = std::chrono::system_clock::now();
        o.colision(*this);
        exploded = true;
        an_type = AnimationType::EXPLOSION;
    }
}

void Rocket::colision(Enemigo& e) {
    tiempo = std::chrono::system_clock::now();
    e.colision(*this);
    exploded = true;
    an_type = AnimationType::EXPLOSION;
    x += e.width / 2;
}

void Rocket::colision(Personaje& p) {
    p.colision(*this);
    if (p.id != shooter_id) {
        tiempo = std::chrono::system_clock::now();
        exploded = true;
        an_type = AnimationType::EXPLOSION;
        x += p.width / 2;
    }
}

void Rocket::update(
        Mapa& mapa, ListaObjetos& objetos,
        Queue<Container>& q) {  // actualiza la posicion, si choca con el mapa se tiene que borrar

    if (exploded && std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::system_clock::now() - tiempo)
                                    .count() > wait_explosion) {
        borrar = true;
        return;
    }

    if (exploded) {

        Container c(0, this->id, this->x - 1, this->y - 1, this->width + 2, this->height + 2,
                    this->d, this->an_type, this->en_type, 0, {EntityType::NONE_ENTITY, 0}, 0, "");
        q.try_push(c);

        return;
    }

    x += vel;

    if (mapa.CheckColision(x, y, width, height)) {
        this->borrar = true;
    }
    Container c(0, this->id, this->x, this->y, this->width, this->height, this->d, this->an_type,
                this->en_type, 0, {EntityType::NONE_ENTITY, 0}, 0, "");
    q.try_push(c);
}
