#ifndef SPAZ_H
#define SPAZ_H

#include <chrono>
#include <map>
#include <string>
#include <vector>

#include "../../common_src/headers/queue.h"

#include "character.h"
#include "map.h"
#include "object.h"

class Spaz: public Character {
private:
    int wait_sidekick;

    virtual void update_position() override;
    void stop_special_action();
    virtual void check_special_action(bool col_x, bool col_y) override;

public:
    Spaz(float x, float y, std::map<std::string, float>& config, Queue<Container>& q,
         std::string name);
    virtual void special_action() override;
};

#endif
