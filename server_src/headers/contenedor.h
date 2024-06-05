#ifndef CONTENEDOR_H_
#define CONTENEDOR_H_

#include <vector>

#include "../../common_src/headers/entity_commands.h"

class Contenedor {
private:
    std::vector<float> vector;

public:
    Contenedor(int msg_code, int id, float x, float y, float w, float h, int direccion,
               AnimationType an_type, EntityType en_type, int vida, int municion, int score);
    int msg_code();
    int id();
    float posx();
    float posy();
    float width();
    float height();
    int direccion();
    int vida();
    int municion();
    int score();
    AnimationType animation_type();
    EntityType entity_type();
};
#endif
