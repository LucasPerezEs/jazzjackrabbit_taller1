#ifndef GHOST_H_
#define GHOST_H_

#include <map>
#include <memory>
#include <string>
#include <unordered_map>

#include "../../common_src/headers/queue.h"

#include "bullet_ammo.h"
#include "carrot.h"
#include "character.h"
#include "enemy.h"
#include "gold_coin.h"
#include "object.h"
#include "object_list.h"

class ObjectList;

class Ghost: public Enemy {
protected:
    float lim_x_izq;
    float lim_x_der;
    float lim_y;

public:
    Ghost(float x, float y, std::map<std::string, float>& config);
    virtual void update(Map& m, ObjectList& objetos, Queue<Container>& q) override;
    virtual void update_vivo(ObjectList& objetos, Queue<Container>& q,
                             std::map<uint32_t, std::shared_ptr<Character>>& clientCharacters,
                             std::shared_ptr<Entity> e) override;
};


#endif
