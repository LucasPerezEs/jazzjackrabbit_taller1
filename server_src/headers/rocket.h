#ifndef ROCKET_H
#define ROCKET_H

#include <map>
#include <string>

#include "projectile.h"

class Rocket: public Projectile {
private:
    std::chrono::system_clock::time_point tiempo;
    int wait_explosion;
    bool exploded;

public:
    Rocket(float x, float y, int d, int shooter_id, std::map<std::string, float>& config);
    virtual void colision(Object& o) override;
    virtual void colision(Enemy& e) override;
    virtual void colision(Character& p) override;
    virtual void update(Map& m, ObjectList& objetos, Queue<Container>& q) override;
};


#endif
