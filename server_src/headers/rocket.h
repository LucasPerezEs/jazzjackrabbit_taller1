#ifndef ROCKET_H
#define ROCKET_H

#include <map>
#include <string>

#include "projectile.h"

class Rocket: public Projectile {
public:
    Rocket(float x, float y, int d, int shooter_id, std::map<std::string, float>& config);
};


#endif
