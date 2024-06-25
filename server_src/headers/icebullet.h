#ifndef ICEBULLET_H
#define ICEBULLET_H

#include <map>
#include <string>

#include "projectile.h"

class IceBullet: public Projectile {

public:
    IceBullet(float x, float y, int d, int shooter_id, std::map<std::string, float>& config);
};

#endif
