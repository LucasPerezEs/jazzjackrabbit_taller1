#include "../headers/enemy.h"

#include <iostream>

#include "../headers/projectile.h"


Enemy::Enemy(float x, float y, float w, float h, float max_life, float speed, float damage,
             float prob_carrot, float prob_ammo, float prob_goldcoin, float prob_rocket,
             float prob_gem, float prob_icebullet, EntityType en_type, AnimationType an_type,
             std::map<std::string, float>& config):
        Entity(x, y, w, h, max_life, en_type, an_type),
        max_life(max_life),
        damage(damage),
        speed(speed),
        prob_carrot(prob_carrot),
        prob_ammo(prob_ammo),
        prob_goldcoin(prob_goldcoin),
        prob_rocket(prob_rocket),
        prob_gem(prob_gem),
        prob_icebullet(prob_icebullet),
        frozen(false),
        frozen_time(config["ice_bullet_frozen_time"]),
        config(config) {
    direccion = 1;
    contador = 0;
    spawn = 1;
}

void Enemy::colision(Object& o) {
    if (check_colision(o)) {
        o.colision(*this);
    }
}
void Enemy::colision(Character& p) { p.colision(*this); }

void Enemy::colision(Projectile& b) {
    if (b.en_type != EntityType::ROCKET) {
        b.borrar = true;
    }

    if (b.en_type == EntityType::ICE_BULLET) {
        frozen = true;
        frozen_start = std::chrono::system_clock::now();
    }

    RecibirDanio(b.danio);
}

void Enemy::drop_item(ObjectList& objetos, Queue<Container>& q) {
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

        if (random_carrot < 75) {
            std::shared_ptr<Carrot> drop(new Carrot(x + width / 2, y + height / 3, config, q));
            objetos.agregar_objeto(drop);
            Container c(0, drop->id, drop->x, drop->y, drop->width, drop->height, 0, drop->an_type,
                        drop->en_type, 0, {EntityType::NONE_ENTITY, 0}, 0, "");
            q.try_push(c);
        } else {
            std::shared_ptr<PoisonedCarrot> drop(
                    new PoisonedCarrot(x + width / 2, y + height / 3, config, q));
            objetos.agregar_objeto(drop);
            Container c(0, drop->id, drop->x, drop->y, drop->width, drop->height, 0, drop->an_type,
                        drop->en_type, 0, {EntityType::NONE_ENTITY, 0}, 0, "");
            q.try_push(c);
        }

    } else if (random_int < prob_goldcoin + prob_carrot + prob_ammo) {
        std::shared_ptr<BulletAmmo> drop(new BulletAmmo(x + width / 2, y + height / 3, config, q));
        objetos.agregar_objeto(drop);
        Container c(0, drop->id, drop->x, drop->y, drop->width, drop->height, 0, drop->an_type,
                    drop->en_type, 0, {EntityType::NONE_ENTITY, 0}, 0, "");
        q.try_push(c);

    } else if (random_int < prob_goldcoin + prob_carrot + prob_ammo + prob_rocket) {
        std::shared_ptr<RocketAmmo> drop(new RocketAmmo(x + width / 2, y + height / 3, config, q));
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

    } else if (random_int <
               prob_goldcoin + prob_carrot + prob_ammo + prob_rocket + prob_gem + prob_icebullet) {
        std::shared_ptr<IceBulletAmmo> drop(
                new IceBulletAmmo(x + width / 2, y + height / 3, config, q));
        objetos.agregar_objeto(drop);
        Container c(0, drop->id, drop->x, drop->y, drop->width, drop->height, 0, drop->an_type,
                    drop->en_type, 0, {EntityType::NONE_ENTITY, 0}, 0, "");
        q.try_push(c);

    } else {
        return;
    }
}

int Enemy::get_damage() { return this->damage; }

void Enemy::check_frozen() {
    if (frozen) {
        auto now = std::chrono::system_clock::now();
        auto duration =
                std::chrono::duration_cast<std::chrono::seconds>(now - frozen_start).count();

        if (duration >= frozen_time) {
            frozen = false;
        }
    }
}
