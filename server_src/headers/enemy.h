#ifndef ENEMIGO_H_
#define ENEMIGO_H_

#include <map>
#include <memory>
#include <string>
#include <unordered_map>

#include "../../common_src/headers/queue.h"

#include "bullet_ammo.h"
#include "carrot.h"
#include "character.h"
#include "gem.h"
#include "gold_coin.h"
#include "icebullet_ammo.h"
#include "object.h"
#include "object_list.h"
#include "rocket_ammo.h"

class Projectile;
class ObjectList;

class Enemy: public Entity {
protected:
    float max_life;
    int damage;
    float speed;
    float prob_carrot;
    float prob_ammo;
    float prob_goldcoin;
    float prob_rocket;
    float prob_gem;
    float prob_icebullet;
    bool frozen;
    float frozen_time;
    std::chrono::system_clock::time_point frozen_start;
    std::map<std::string, float>& config;

    void check_frozen();

public:
    Enemy(float x, float y, float w, float h, float max_life, float speed, float damage,
          float prob_carrot, float prob_ammo, float prob_goldcoin, float prob_rocket,
          float prob_gem, float prob_icebullet, EntityType en_type, AnimationType an_type,
          std::map<std::string, float>& config);
    virtual void colision(Object& o) override;
    virtual void colision(Character& p) override;
    virtual void colision(Projectile& b) override;
    virtual void update(Map& m, ObjectList& objetos, Queue<Container>& q) override = 0;
    virtual void update_vivo(ObjectList& objetos, Queue<Container>& q,
                             std::map<uint32_t, std::shared_ptr<Character>>& clientCharacters,
                             std::shared_ptr<Entity> e) override = 0;
    virtual void drop_item(ObjectList& objetos, Queue<Container>& q);
    int get_damage();
};


#endif
