#ifndef BANANA_H_
#define BANANA_H_

#include <map>
#include <string>

#include "../../common_src/headers/entity_commands.h"
#include "../../common_src/headers/queue.h"

#include "character.h"
#include "map.h"
#include "object.h"
#include "pickup.h"

class Banana: public Object {
protected:
    float vel;

public:
    int danio;
    Banana(float x, float y, int d, std::map<std::string, float>& config);
    virtual void colision(Object& o) override;
    virtual void colision(Character& o) override;
    virtual void colision(Enemy& o) override;
    virtual void colision(Pickup& o) override;
    virtual void update(Map& m, ObjectList& objetos, Queue<Container>& q) override;
    virtual void eliminar() override;
};

#endif
