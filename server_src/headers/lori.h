#ifndef LORI_H
#define LORI_H

#include <chrono>
#include <map>
#include <string>
#include <vector>

#include "../../common_src/headers/queue.h"

#include "mapa.h"
#include "objeto.h"
#include "personaje.h"

class Lori: public Personaje {

public:
    Lori(float x, float y, std::map<std::string, float>& config, Queue<Container>& q);
    virtual void special_action() override;
    virtual void check_special_action(bool col_x, bool col_y) override;
};

#endif
