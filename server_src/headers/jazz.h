#ifndef JAZZ_H
#define JAZZ_H

#include <chrono>
#include <map>
#include <string>
#include <vector>

#include "../../common_src/headers/queue.h"

#include "contenedor.h"
#include "mapa.h"
#include "objeto.h"
#include "personaje.h"

class Jazz: public Personaje {

public:
    Jazz(float x, float y, std::map<std::string, float>& config);
    virtual void special_action() override;
};

#endif
