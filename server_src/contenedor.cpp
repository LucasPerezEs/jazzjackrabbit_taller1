#include "headers/contenedor.h"

Contenedor::Contenedor(int msg_code, int id, float x, float y, float w, float h, int direccion,
                       AnimationType an_type, EntityType en_type, int vida, int municion,
                       int score) {
    vector.push_back(msg_code);
    vector.push_back(id);
    vector.push_back(x);
    vector.push_back(y);
    vector.push_back(w);
    vector.push_back(h);
    vector.push_back(direccion);
    vector.push_back(an_type);
    vector.push_back(en_type);
    vector.push_back(vida);
    vector.push_back(municion);
    vector.push_back(score);
}

int Contenedor::msg_code() { return vector[0]; }

int Contenedor::id() { return vector[1]; }

float Contenedor::posx() { return vector[2]; }

float Contenedor::posy() { return vector[3]; }

float Contenedor::width() { return vector[4]; }

float Contenedor::height() { return vector[5]; }

int Contenedor::direccion() { return vector[6]; }

AnimationType Contenedor::animation_type() { return (AnimationType)vector[7]; }

EntityType Contenedor::entity_type() { return (EntityType)vector[8]; }

int Contenedor::vida() { return vector[9]; }

int Contenedor::municion() { return vector[10]; }

int Contenedor::score() { return vector[11]; }
