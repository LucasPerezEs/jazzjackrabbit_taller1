#ifndef BULLET_H
#define BULLET_H

#include <map>
#include <string>

#include "projectile.h"

class Bullet: public Projectile {
public:
    Bullet(float x, float y, int d, int shooter_id, std::map<std::string, float>& config);
};

#endif
