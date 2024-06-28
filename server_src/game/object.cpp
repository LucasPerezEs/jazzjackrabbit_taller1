#include "../headers/object.h"

#include <iostream>
#include <vector>

#include "../headers/enemy.h"
#include "../headers/map.h"
#include "../headers/object_list.h"
#include "../headers/projectile.h"

int cant = 1;
int num = 20;

Object::Object(float x, float y, float w, float h, EntityType en_type, AnimationType an_type):
        x(x), y(y), width(w), height(h), borrar(false), en_type(en_type), an_type(an_type) {
    id = num;
    num++;
}

// cppcheck-suppress uninitMemberVar
Entity::Entity(float x, float y, float w, float h, int vida, EntityType en_type,
               AnimationType an_type):
        Object(x, y, w, h, en_type, an_type), direccion(1), contador(0), vida(vida) {
    killed = false;
}


void Object::update(Map& m, ObjectList& objetos, Queue<Container>& q) {}
void Object::eliminar() {}

bool Object::check_colision(Object& o) {
    if (this == &o) {
        return false;
    }
    if (x < (o.x + o.width) && (x + width) > o.x && y < (o.y + o.height) && (y + height) > o.y) {
        return true;
    }
    return false;
}

void Object::colision(Character& o) {}  //       Por defecto los objetos no hacen nada
void Object::colision(Enemy& o) {}
void Object::colision(Projectile& o) {}
void Object::colision(Pickup& o) {}
void Object::colision(BulletAmmo& m) {}
void Object::colision(Banana& b) {}
void Object::colision(PoisonedCarrot& ze) {}

Object::~Object() {}

void Entity::RecibirDanio(int d) {
    vida -= d;
    if (vida <= 0) {
        borrar = true;
    }
}

bool Entity::vivo() { return vida > 0; }

void Entity::update_vivo(ObjectList& objetos, Queue<Container>& q,
                         std::map<uint32_t, std::shared_ptr<Character>>& clientCharacters,
                         std::shared_ptr<Entity> e) {
    if (vida <= 0) {
        if (!killed) {
            killed = true;
            last_killed = std::chrono::system_clock::now();
        } else if (std::chrono::duration_cast<std::chrono::milliseconds>(
                           std::chrono::system_clock::now() - last_killed)
                           .count() >= 3000) {
            killed = false;
            vida = 100;
            borrar = false;
            objetos.agregar_objeto(e);
            Container c(0, this->id, this->x, this->y, this->width, this->height, this->direccion,
                        this->an_type, this->en_type, 0, {EntityType::NONE_ENTITY, 0}, 0, "");
            q.try_push(c);
        }
    }
}
