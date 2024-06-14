#ifndef SPAZ_H
#define SPAZ_H

#include <chrono>
#include <map>
#include <string>
#include <vector>

#include "../../common_src/headers/queue.h"

#include "contenedor.h"
#include "mapa.h"
#include "objeto.h"
#include "personaje.h"

class Spaz: public Personaje {
private:
    int wait_sidekick;

    virtual void check_colisions(Mapa& m, int aux_x, int aux_y) override;
    virtual void update_position() override;
    void stop_special_action();

public:
    Spaz(float x, float y, std::map<std::string, float>& config);
    virtual void special_action() override;
};

#endif
