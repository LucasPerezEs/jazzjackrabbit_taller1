#ifndef LORI_H
#define LORI_H

#include <chrono>
#include <map>
#include <string>
#include <vector>

#include "../../common_src/headers/queue.h"

#include "character.h"
#include "map.h"
#include "object.h"

class Lori: public Character {

public:
    Lori(float x, float y, std::map<std::string, float>& config, Queue<Container>& q,
         std::string name);
    virtual void special_action() override;
    virtual void check_special_action(bool col_x, bool col_y) override;
};

#endif
