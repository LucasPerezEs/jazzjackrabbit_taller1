#include "../headers/projectile.h"

#include "../headers/character.h"

Projectile::Projectile(float x, float y, int d, int shooter_id, EntityType en_type,
                       AnimationType an_type, int vel, int danio):
        Object(x, y, 1, 1, en_type, an_type),
        vel(vel * d),
        shooter_id(shooter_id),
        d(d),
        danio(danio) {}

void Projectile::colision(Object& o) {
    if (check_colision(o)) {
        o.colision(*this);
    }
}

void Projectile::colision(Enemy& e) { e.colision(*this); }

void Projectile::colision(Character& p) { p.colision(*this); }


void Projectile::update(
        Map& mapa, ObjectList& objetos,
        Queue<Container>& q) {  // actualiza la posicion, si choca con el mapa se tiene que borrar
    x += vel;

    if (mapa.CheckColision(x, y, width, height)) {
        if (en_type != EntityType::ROCKET) {
            this->borrar = true;
        }
    }
    Container c(0, this->id, this->x, this->y, this->width, this->height, this->d, this->an_type,
                this->en_type, 0, {EntityType::NONE_ENTITY, 0}, 0, "");
    q.try_push(c);
}

void Projectile::eliminar() {  // Para los memory leaks
    delete (this);
}

int Projectile::get_shooter_id() { return this->shooter_id; }
